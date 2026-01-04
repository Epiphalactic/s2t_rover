# Brain ↔ Spine Message Contract (v0.2)

Status: Normative Specification  
Applies to: S2T Rover “Brain” (SBC) ↔ “Spine” (MCU) link  
Primary goal (Stage 2): Infrastructure hardening: safety gating, deterministic liveness, and observability over a stable message interface.  
Non-goals: Autonomy, feature work, sensor taxonomies, multi-node discovery, security/encryption, CAN bus electrical/arbitration specifics.

---

## 1. Definitions

- Brain: High-level compute node (Linux-class) responsible for orchestration, UI, logging, and deployments.
- Spine: Real-time microcontroller node responsible for hardware interfacing, safety reflexes, and motion authority.
- Transport: A byte-delivery mechanism (e.g., USB serial now; CAN later). The message contract is independent of transport.
- Packet: One complete contract-defined message (header + payload + trailer).
- Session: A Brain boot instance interacting with a Spine boot instance.
- Axis: A controllable degree of freedom exposed by Spine (e.g., left/right drive). Axes are identified by axis_id.

---

## 2. Roles and Authority

### 2.1 Spine is the final authority for motion
Spine MUST enforce all safety rules locally, independent of Brain correctness, timing, or availability.

### 2.2 Brain does not directly drive hardware
Brain MUST NOT issue hardware-specific commands (PWM duty, phase current, controller-specific registers).  
Brain MAY only issue contract-defined requests (e.g., enable/disable and abstract setpoints).

### 2.3 Safe by default
Upon boot, link loss, protocol error, or fault escalation, Spine MUST transition to a safe condition in which motion output is disabled.

---

## 3. Safety Invariants (Hard Rules)

### 3.1 Silence equals stop
If Spine is in a motion-enabled state and does not receive valid keepalive traffic within the configured hold timeout, Spine MUST disable motion and transition to SAFE (or FAULT if appropriate).

### 3.2 Keepalive traffic definition (Frozen for v0.1)
For v0.1, keepalive traffic is defined as:

- Receipt of a valid B2S_HEARTBEAT packet

Setpoints SHALL NOT count as keepalive traffic.

### 3.3 Setpoints are not permissions
Spine MUST ignore setpoints unless motion is enabled and the session is valid.

### 3.4 Clamping and refusal
Spine MUST clamp or refuse out-of-range setpoints according to the axis limits it has declared.  
If refused, Spine MUST emit an error acknowledgement and/or fault as defined in this contract.

### 3.5 Timeout must be enforced by Spine
Brain MUST NOT be relied upon to stop motion on loss of link. Any Brain-side “stop” behavior is a secondary safety measure only.

---

## 4. Versioning and Compatibility

### 4.1 Protocol version fields
Protocol version fields (proto_major, proto_minor) are included in every packet.

- v0.x indicates breaking changes may occur between minor revisions
- Within a single repo release, versions MUST match across Brain and Spine

### 4.2 Forward compatibility rule
- A receiver MUST reject packets with an unknown proto_major
- A receiver MAY reject packets with a higher proto_minor than it supports

---

## 5. Packet Format (Transport-Agnostic)

### 5.1 Byte order
Little-endian for all multi-byte fields.

### 5.2 Packet structure
[Header][Payload (0..N bytes)][Trailer]

### 5.3 Header (Fixed)

All fields are mandatory.

Field            | Type | Meaning
-----------------|------|-----------------------------------------------
magic            | u16  | Protocol identifier
proto_major      | u8   | Major version
proto_minor      | u8   | Minor version
msg_type         | u8   | Message type enum
flags            | u8   | Flags bitfield
src              | u8   | Source node ID (Brain=0, Spine=1)
dst              | u8   | Destination node ID
seq              | u16  | Sequence number (per source)
payload_len      | u16  | Payload length in bytes
header_crc16     | u16  | CRC-16 of header with this field zeroed

### 5.4 Trailer (Fixed)

Field            | Type | Meaning
-----------------|------|--------------------------------
payload_crc32    | u32  | CRC-32 of payload bytes (0 if no payload)

### 5.5 Integrity requirements

- Receiver MUST validate magic
- Receiver MUST validate header_crc16
- Receiver MUST validate payload_crc32 when payload_len > 0
- On failure, packet MUST be discarded and MUST NOT affect motion enable state except via timeout rules

### 5.6 Framing (stream transports)
For stream transports (e.g., USB serial), receiver MUST resynchronize using magic and payload_len.

### 5.7 Protocol Magic (Frozen for v0.1)

    PROTO_MAGIC = 0x5332   // mnemonic: "S2"

Packets with mismatched magic MUST be discarded.

### 5.8 CRC Definitions (Frozen for v0.2)

To remove ambiguity, CRC algorithms are defined explicitly.

#### 5.8.1 Header CRC (`header_crc16`)

`header_crc16` SHALL use CRC-16/CCITT-FALSE with parameters:

- width: 16
- poly: 0x1021
- init: 0xFFFF
- refin: false
- refout: false
- xorout: 0x0000

Computation rule:
- Compute the CRC over the full header byte sequence with `header_crc16` treated as zero.
- Multi-byte fields remain little-endian in the header as transmitted.

#### 5.8.2 Payload CRC (`payload_crc32`)

`payload_crc32` SHALL use CRC-32/ISO-HDLC (CRC-32/IEEE 802.3) with parameters:

- width: 32
- poly: 0x04C11DB7
- init: 0xFFFFFFFF
- refin: true
- refout: true
- xorout: 0xFFFFFFFF

Computation rule:
- Compute the CRC over the payload bytes only (exactly `payload_len` bytes).
- If `payload_len == 0`, `payload_crc32` SHALL be 0.

---

## 6. Node IDs (v0.1)

- 0 = Brain
- 1 = Spine

All other IDs are reserved.

---

## 7. State Model (Spine)

Spine MUST expose a state value in HEARTBEAT and STATE_REPORT.

State enum (v0.1):

- INIT    : Booting / not ready
- SAFE    : Motion disabled; ready to enable
- ENABLED : Motion permitted
- FAULT   : Motion disabled due to fault

Spine MUST start in INIT and transition to SAFE when ready.  
Spine MUST NOT enter ENABLED unless it has accepted MOTION_ENABLE(enable=1) for the current session.

### 7.1 Spine State Enum Numeric Values (Normative)

The following numeric values are normative and SHALL be used wherever the Spine
state is encoded or reported.

| State Name | Value (uint8) | Meaning |
|-----------:|:--------------|:--------|
| INIT       | 0x00          | Booting / not yet ready |
| SAFE       | 0x01          | Motion disabled, awaiting enable |
| ENABLED    | 0x02          | Motion permission granted (subject to liveness) |
| FAULT      | 0x03          | Fault latched; motion disabled |

Values 0x04–0xFF are RESERVED for future use.

---

## 8. Message Types and Semantics (v0.1)

Prefixes:
- Brain to Spine: B2S_
- Spine to Brain: S2B_

Defined message types:

- B2S_HELLO
- S2B_IDENTITY
- B2S_HEARTBEAT
- S2B_HEARTBEAT
- B2S_MOTION_ENABLE
- B2S_MOTION_SETPOINT
- S2B_STATE_REPORT
- S2B_FAULT
- S2B_ACK

(Full payload definitions as previously adopted.)

### 8.1 Brain → Spine Message Type IDs (Normative)

The following message type IDs are normative and SHALL be used in the packet
header `msg_type` field for Brain → Spine messages.

| Message Type        | ID (uint8) | Purpose |
|--------------------:|:-----------|:--------|
| B2S_HELLO           | 0x10       | Session initiation / identity |
| B2S_HEARTBEAT       | 0x11       | Liveness keepalive |
| B2S_MOTION_ENABLE   | 0x12       | Grant or revoke motion permission |
| B2S_MOTION_SETPOINT | 0x13       | Motion setpoint (never implies permission) |

IDs 0x14–0x2F are RESERVED for future Brain → Spine messages.

### 8.2 Spine → Brain Message Type IDs (Normative)

The following message type IDs are normative and SHALL be used in the packet
header `msg_type` field for Spine → Brain messages.

| Message Type      | ID (uint8) | Purpose |
|------------------:|:-----------|:--------|
| S2B_IDENTITY      | 0x80       | Spine identity / version report |
| S2B_HEARTBEAT     | 0x81       | Spine liveness + state |
| S2B_STATE_REPORT  | 0x82       | Periodic detailed state report |
| S2B_ACK           | 0x83       | Acknowledgment / rejection |
| S2B_FAULT         | 0x84       | Fault announcement |

IDs 0x85–0x9F are RESERVED for future Spine → Brain messages.

### 8.3 Payload Layouts (v0.2 — Normative)

This section defines the exact byte-level payload layouts for all v0.2 message types
listed in Section 8. Payload layouts are REQUIRED for compliance.

#### 8.3.1 Common Rules (Normative)

- All multi-byte fields are little-endian (per Section 5.1).
- All payloads are packed byte sequences with no padding.
- `payload_len` MUST exactly match the message’s required payload length.
  - If `payload_len` does not match, the receiver MUST reject the message and MUST NOT
    treat it as keepalive traffic.
- Reserved fields:
  - Senders MUST set all RESERVED bytes to 0.
  - Receivers MUST ignore RESERVED bytes.
- Floating-point:
  - Any `f32` field SHALL be IEEE-754 binary32, little-endian.
  - NaN or ±Inf values MUST be rejected.

#### 8.3.2 Session Validity Primitive (Normative)

To support `SESSION_INVALID` fault code (Table 11), this contract defines a minimal
session identifier carried in payloads:

- `session_id` is a `u32` selected by the Brain.
- `session_id = 0` is RESERVED and MUST NOT be used to start a session.
- The Spine maintains `current_session_id`:
  - Initial value on boot: `0`.
  - On accepting a valid `B2S_HELLO(session_id != 0)`, Spine sets `current_session_id`
    to that value and immediately transitions to SAFE (motion disabled).
  - Any Brain→Spine message that includes a `session_id` and does not match
    `current_session_id` MUST be rejected (and MAY raise fault `SESSION_INVALID`).
- Session requirements:
  - `B2S_HEARTBEAT`, `B2S_MOTION_ENABLE`, and `B2S_MOTION_SETPOINT` REQUIRE an active
    session (`current_session_id != 0`).
  - If no session is active, these messages MUST be rejected and MUST NOT count as keepalive.

This definition is additive and does not grant authority. It only enables deterministic
rejection of stale/foreign senders.

#### 8.3.3 Brain → Spine Payloads (Normative)

##### B2S_HELLO (msg_type 0x10)
Purpose: initiate/replace session (does not grant motion authority).

Required payload length: 4 bytes

Field        | Type | Offset | Notes
------------|------|--------|---------------------------
session_id   | u32  | 0      | MUST be nonzero

Spine behavior constraints:
- On accepting a valid HELLO, Spine MUST disable motion and enter SAFE.

##### B2S_HEARTBEAT (msg_type 0x11)
Purpose: keepalive traffic (per Section 3.2).

Required payload length: 8 bytes

Field           | Type | Offset | Notes
---------------|------|--------|---------------------------
session_id      | u32  | 0      | MUST equal current_session_id
brain_uptime_ms | u32  | 4      | Monotonic since Brain boot; informational

##### B2S_MOTION_ENABLE (msg_type 0x12)
Purpose: request motion permission grant/revoke.

Required payload length: 8 bytes

Field        | Type | Offset | Notes
------------|------|--------|---------------------------
session_id   | u32  | 0      | MUST equal current_session_id
enable       | u8   | 4      | 0 = disable, 1 = enable
reserved     | u8[3]| 5      | MUST be 0

Validity:
- `enable` values other than 0/1 MUST be rejected.

##### B2S_MOTION_SETPOINT (msg_type 0x13)
Purpose: setpoint for one axis (never implies permission).

Required payload length: 12 bytes

Field        | Type | Offset | Notes
------------|------|--------|---------------------------
session_id   | u32  | 0      | MUST equal current_session_id
axis_id      | u8   | 4      | MUST exist in Axis Table (Section 10)
reserved0    | u8   | 5      | MUST be 0
value        | f32  | 6      | Units per Axis Table; must be finite
reserved1    | u16  | 10     | MUST be 0

Range:
- `value` MUST be within [min,max] for the axis (Section 10) or be refused per Section 3.4.

#### 8.3.4 Spine → Brain Payloads (Normative)

##### S2B_IDENTITY (msg_type 0x80)
Purpose: identity + session echo for observability.

Required payload length: 12 bytes

Field           | Type | Offset | Notes
---------------|------|--------|---------------------------
spine_boot_id   | u32  | 0      | Random or unique per Spine boot; stable until reset
spine_uptime_ms | u32  | 4      | Monotonic since Spine boot; informational
session_id      | u32  | 8      | Current session_id (0 if none)

##### S2B_HEARTBEAT (msg_type 0x81)
Purpose: Spine liveness + state.

Required payload length: 12 bytes

Field           | Type | Offset | Notes
---------------|------|--------|---------------------------
session_id      | u32  | 0      | Current session_id (0 if none)
spine_uptime_ms | u32  | 4      | Monotonic since Spine boot; informational
spine_state     | u8   | 8      | Values per Section 7.1
motion_permitted| u8   | 9      | 0 = no, 1 = yes (logical permission only)
reserved        | u16  | 10     | MUST be 0

##### S2B_STATE_REPORT (msg_type 0x82)
Purpose: periodic state snapshot (lightweight in v0.2).

Required payload length: 12 bytes

Field           | Type | Offset | Notes
---------------|------|--------|---------------------------
session_id      | u32  | 0      | Current session_id (0 if none)
spine_uptime_ms | u32  | 4      | Monotonic since Spine boot; informational
spine_state     | u8   | 8      | Values per Section 7.1
flags           | u8   | 9      | Bit0: motion_permitted, Bit1: fault_latched; others RESERVED
active_fault    | u16  | 10     | 0 = none, else fault_code from Section 11

##### S2B_ACK (msg_type 0x83)
Purpose: acknowledge/reject a received Brain→Spine message.

Required payload length: 12 bytes

Field        | Type | Offset | Notes
------------|------|--------|---------------------------
session_id   | u32  | 0      | Current session_id (0 if none)
acked_type   | u8   | 4      | The msg_type being acknowledged
result       | u8   | 5      | 0 = OK, 1 = REJECTED
acked_seq    | u16  | 6      | The header `seq` of the acknowledged packet
fault_code   | u16  | 8      | 0 = none, else Section 11 fault_code
reserved     | u16  | 10     | MUST be 0

##### S2B_FAULT (msg_type 0x84)
Purpose: announce a fault condition.

Required payload length: 16 bytes

Field           | Type | Offset | Notes
---------------|------|--------|---------------------------
session_id      | u32  | 0      | Current session_id (0 if none)
spine_uptime_ms | u32  | 4      | Monotonic since Spine boot; informational
fault_code      | u16  | 8      | Must match Section 11 table
severity        | u8   | 10     | 1 = WARN, 2 = ERROR, 3 = FATAL
spine_state     | u8   | 11     | Values per Section 7.1
disables_motion | u8   | 12     | 0 = no, 1 = yes (must match Section 11)
reserved        | u8[3]| 13     | MUST be 0


### Message ID Allocation Policy (Normative)

- Message type IDs are uint8.
- Brain → Spine messages SHALL use IDs in the range 0x10–0x2F.
- Spine → Brain messages SHALL use IDs in the range 0x80–0x9F.
- IDs outside these ranges are RESERVED.
- IDs, once assigned, SHALL NOT be reused or repurposed.

---

## 9. Timing Requirements (Frozen for v0.1)

    B2S_HEARTBEAT_PERIOD_MS   = 200
    S2B_HEARTBEAT_PERIOD_MS   = 100
    DEFAULT_HOLD_TIMEOUT_MS  = 500
    STATE_REPORT_PERIOD_MS   = 750

Spine MUST disable motion if keepalive traffic is absent longer than the active hold timeout.

---

## 10. Axis Table (v0.1 — Normative)

Axes are declared even though motion is not yet implemented.  
Declaration does NOT imply actuation exists.

axis_id | name        | supports | unit_code | min   | max
--------|-------------|----------|-----------|-------|------
0       | drive_left  | velocity | mps       | -0.50 | +0.50
1       | drive_right | velocity | mps       | -0.50 | +0.50

Rules:
- axis_id assignments MUST remain stable
- Spine MUST clamp or refuse values outside bounds
- Brain MUST NOT assume undeclared axes

---

## 11. Fault Codes (v0.1 — Normative)

fault_code | name                 | severity | disables_motion | notes
-----------|----------------------|----------|-----------------|----------------------
1001 | CRC_HEADER_FAIL        | ERROR | yes | header CRC invalid
1002 | CRC_PAYLOAD_FAIL       | ERROR | yes | payload CRC invalid
1003 | UNKNOWN_MSG_TYPE       | WARN  | no  | ignored, logged
1004 | SESSION_INVALID        | ERROR | yes | boot/session mismatch
1005 | KEEPALIVE_TIMEOUT      | FATAL | yes | silence=stop invariant
1006 | INVALID_AXIS_ID        | ERROR | yes | axis not declared
1007 | SETPOINT_OUT_OF_RANGE  | ERROR | yes | refused by policy
1099 | INTERNAL_ERROR         | FATAL | yes | generic catch-all

Rules:
- ERROR or FATAL faults MUST disable motion immediately
- Fault state MUST appear in subsequent heartbeats
- Unknown fault codes MUST be treated as ERROR

---

## 12. Transport Notes

### 12.1 USB (maintenance path)
USB is an approved transport and MAY remain enabled indefinitely.

### 12.2 CAN (future backbone)
CAN SHALL carry the same canonical packets. Fragmentation MUST preserve original packet bytes.

---

## 13. Compliance

An implementation is compliant with v0.2 if it:

- Produces and accepts packets per Section 5
- Enforces safety invariants per Section 3
- Implements required message types per Section 8
- Enforces timing per Section 9
- Publishes and respects the axis table per Section 10

---

## 14. Authority Statement

With these freezes applied:

- The Brain ↔ Spine Message Contract v0.2 is fully specified
- No implicit safety behavior exists
- All future implementation work is testable against this document

Any deviation requires:
- A protocol version change, and
- An explicit Decision Log entry
