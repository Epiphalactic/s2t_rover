

# Brain ↔ Spine Message Contract (v0.1)

**Status:** Normative Specification
**Applies to:** S2T Rover “Brain” (SBC) ↔ “Spine” (MCU) link
**Primary goal (Stage 2):** Infrastructure hardening: safety gating, deterministic liveness, and observability over a stable message interface.
**Non-goals:** Autonomy, feature work, sensor taxonomies, multi-node discovery, security/encryption, CAN bus electrical/arbitration specifics.

---

## 1. Definitions

* **Brain:** High-level compute node (Linux-class) responsible for orchestration, UI, logging, deployments.
* **Spine:** Real-time microcontroller node responsible for hardware interfacing, safety reflexes, and motion authority.
* **Transport:** A byte-delivery mechanism (e.g., USB serial now; CAN later). The message contract is independent of transport.
* **Packet:** One complete contract-defined message (header + payload + trailer).
* **Session:** A Brain boot instance interacting with a Spine boot instance.
* **Axis:** A controllable degree of freedom exposed by Spine (e.g., left/right drive). Axes are identified by `axis_id`.

---

## 2. Roles and Authority

2.1 **Spine is the final authority for motion.**
Spine MUST enforce all safety rules locally, independent of Brain correctness, timing, or availability.

2.2 **Brain does not directly drive hardware.**
Brain MUST NOT issue hardware-specific commands (PWM duty, phase current, controller-specific registers). Brain MAY only issue contract-defined requests (e.g., enable/disable and abstract setpoints).

2.3 **Safe by default.**
Upon boot, link loss, protocol error, or fault escalation, Spine MUST transition to a safe condition in which motion output is disabled.

---

## 3. Safety Invariants (Hard Rules)

3.1 **Silence equals stop.**
If Spine is in a motion-enabled state and does not receive valid keepalive traffic within the configured hold timeout, Spine MUST disable motion and transition to `SAFE` (or `FAULT` if appropriate).

3.2 **Keepalive traffic definition.**
For v0.1, keepalive traffic is defined as:

* **(Choose one and freeze it):**

  * Option A (recommended): receipt of a valid `B2S_HEARTBEAT` packet, OR
  * Option B: receipt of a valid `B2S_HEARTBEAT` OR `MOTION_SETPOINT` packet.

3.3 **Setpoints are not permissions.**
Spine MUST ignore setpoints unless motion is enabled and the session is valid.

3.4 **Clamping and refusal.**
Spine MUST clamp or refuse out-of-range setpoints according to the axis limits it has declared. If refused, Spine MUST emit an error acknowledgement and/or fault as defined in this contract.

3.5 **Timeout must be enforced by Spine.**
Brain MUST NOT be relied upon to stop motion on loss of link. Any Brain-side “stop” behavior is a secondary safety measure only.

---

## 4. Versioning and Compatibility

4.1 **Protocol version fields** are included in every packet (`proto_major`, `proto_minor`).

* v0.x indicates breaking changes may occur between minor revisions; however, within a single repo release, the version MUST be consistent across Brain and Spine.

4.2 **Forward compatibility rule.**
A receiver MUST reject packets with an unknown `proto_major`.
A receiver MAY reject packets with a higher `proto_minor` than it supports.

---

## 5. Packet Format (Transport-Agnostic)

5.1 **Byte order**: Little-endian for all multi-byte fields.

5.2 **Packet structure**:
`[Header][Payload (0..N bytes)][Trailer]`

### 5.3 Header (Fixed)

All fields are mandatory.

| Field          | Type | Meaning                                                                   |
| -------------- | ---- | ------------------------------------------------------------------------- |
| `magic`        | u16  | Constant identifying this protocol (fixed value; MUST match on both ends) |
| `proto_major`  | u8   | Major version                                                             |
| `proto_minor`  | u8   | Minor version                                                             |
| `msg_type`     | u8   | Message type enum                                                         |
| `flags`        | u8   | Flags bitfield                                                            |
| `src`          | u8   | Source node id (v0.1: Brain=0, Spine=1)                                   |
| `dst`          | u8   | Destination node id                                                       |
| `seq`          | u16  | Sequence number, increments per `src`                                     |
| `payload_len`  | u16  | Payload length in bytes                                                   |
| `header_crc16` | u16  | CRC-16 of header with this field zeroed                                   |

### 5.4 Trailer (Fixed)

| Field           | Type | Meaning                                           |
| --------------- | ---- | ------------------------------------------------- |
| `payload_crc32` | u32  | CRC-32 of payload bytes (or 0 if `payload_len=0`) |

5.5 **Integrity requirements**

* A receiver MUST validate `magic`.
* A receiver MUST validate `header_crc16`.
* A receiver MUST validate `payload_crc32` when `payload_len > 0`.
* On any validation failure, the packet MUST be discarded and MUST NOT affect motion enable state except as permitted by timeout rules.

5.6 **Framing (stream transports)**
For stream transports (e.g., USB serial), the receiver MUST resynchronize using `magic` and `payload_len` and MUST NOT assume packet boundaries align with reads.

---

## 6. Node IDs (v0.1)

* `0` = Brain
* `1` = Spine

All other IDs are reserved.

---

## 7. State Model (Spine)

Spine MUST expose a state value in `HEARTBEAT` and `STATE_REPORT`.

**State enum (v0.1):**

* `INIT`: Booting / not ready
* `SAFE`: Motion disabled; ready to arm/enable
* `ENABLED`: Motion permitted (subject to hold timeout and faults)
* `FAULT`: Motion disabled due to fault condition

(Additional states like `ARMED` may be introduced later; v0.1 keeps minimal.)

Spine MUST start in `INIT` and transition to `SAFE` when ready. Spine MUST NOT transition to `ENABLED` unless it has accepted a valid `MOTION_ENABLE(enable=1)` request for the current session.

---

## 8. Message Types and Semantics (v0.1)

**Notation:**

* Brain→Spine messages use prefix `B2S_`
* Spine→Brain messages use prefix `S2B_`

### 8.1 `B2S_HELLO`

Purpose: Begin/refresh session and announce Brain presence.

Payload:

* `brain_boot_id` (u32): Random-ish value unique per Brain boot.
* `brain_cap_flags` (u32): Capability bitmap (reserved values allowed).

Rules:

* Brain SHOULD send `B2S_HELLO` at startup and MAY repeat periodically.
* Spine MUST respond with `S2B_IDENTITY` when it accepts a session.

### 8.2 `S2B_IDENTITY`

Purpose: Declare Spine identity and the axis interface.

Payload:

* `spine_boot_id` (u32)
* `spine_fw_version` (u32 or semver packed; project-defined)
* `cap_flags` (u32)
* `axis_count` (u8)
* `axis_desc[axis_count]`:

  * `axis_id` (u8)
  * `supports` (u8 bitflags; v0.1 requires at least velocity OR torque)
  * `unit_code` (u8) (project-defined enum)
  * `reserved` (u8)
  * `min` (f32)
  * `max` (f32)

Rules:

* Spine MUST ensure `axis_id` assignments are stable for a given firmware build.
* Brain MUST treat this as authoritative; Brain MUST NOT assume axes beyond those declared.

### 8.3 `B2S_HEARTBEAT` and `S2B_HEARTBEAT`

Purpose: Liveness and coarse status.

Payload:

* `uptime_ms` (u32)
* `state` (u8)
* `fault_bitmap` (u32)
* `motion_enabled` (u8: 0/1)
* `reserved` (3 bytes)

Rules:

* Brain MUST send `B2S_HEARTBEAT` at the configured interval while connected.
* Spine MUST send `S2B_HEARTBEAT` at the configured interval when running.
* Spine MUST treat absence of required keepalive traffic as a reason to disable motion (Section 3).

### 8.4 `B2S_MOTION_ENABLE`

Purpose: Request enable/disable of motion.

Payload:

* `enable` (u8: 0/1)
* `hold_timeout_ms` (u16)
* `reserved` (u8)
* `command_id` (u32)

Rules:

* Spine MAY refuse enable requests (e.g., in `FAULT` or not in a valid session).
* Spine MUST clamp `hold_timeout_ms` into a project-defined safe range.
* Spine MUST set motion disabled immediately on `enable=0`.
* Spine SHOULD ACK/NACK with `S2B_ACK` including `command_id` as part of status (method defined in 8.8).

### 8.5 `B2S_MOTION_SETPOINT`

Purpose: Provide abstract setpoints per axis.

Payload:

* `command_id` (u32)
* `count` (u8)
* `mode` (u8) (v0.1: `0=velocity`, `1=torque`; others reserved)
* `reserved` (u16)
* `setpoint[count]`:

  * `axis_id` (u8)
  * `reserved` (3 bytes)
  * `value` (f32)

Rules:

* Spine MUST ignore setpoints if motion is not enabled.
* Spine MUST validate `axis_id` and MUST clamp or reject values outside declared `min/max`.
* If rejected, Spine MUST signal error via `S2B_ACK(status!=0)` and/or `S2B_FAULT` depending on severity.
* Brain SHOULD send setpoints at a steady cadence when motion is enabled.

### 8.6 `S2B_STATE_REPORT`

Purpose: Periodic richer telemetry.

Payload (minimal v0.1):

* `uptime_ms` (u32)
* `fault_bitmap` (u32)
* `axis_count` (u8)
* `reserved` (3 bytes)
* `axis_state[axis_count]`:

  * `axis_id` (u8)
  * `reserved` (3 bytes)
  * `measured_value` (f32)

Rules:

* Spine SHOULD send at a slower rate than heartbeat (project-defined).
* `measured_value` MUST be in the declared unit for the axis and appropriate for the current mode.

### 8.7 `S2B_FAULT`

Purpose: Immediate fault notification.

Payload:

* `fault_code` (u16)
* `severity` (u8) (`WARN=1`, `ERROR=2`, `FATAL=3`)
* `reserved` (u8)
* `detail` (u32) (optional; project-defined)

Rules:

* On `ERROR` or `FATAL`, Spine MUST disable motion.
* Spine MUST include fault state/bitmap updates in subsequent heartbeats.

### 8.8 `S2B_ACK` (optional but reserved in v0.1)

Purpose: Acknowledge receipt and result of a request.

Payload:

* `ack_for_msg_type` (u8)
* `reserved` (3 bytes)
* `seq_acked` (u16)
* `status` (u16) (`0=OK`, nonzero=error code)
* `command_id` (u32) (echo from request when present)

Rules:

* If a sender sets `ACK_REQ` flag, receiver SHOULD respond with `S2B_ACK`.
* `status` codes are project-defined; unknown codes MUST be treated as error.

---

## 9. Timing Requirements (v0.1)

These values MUST be defined and frozen for v0.1:

* `B2S_HEARTBEAT_PERIOD_MS = ___` (recommended start: 200 ms)
* `S2B_HEARTBEAT_PERIOD_MS = ___` (recommended start: 100 ms)
* `DEFAULT_HOLD_TIMEOUT_MS = ___` (recommended start: 500 ms)
* `STATE_REPORT_PERIOD_MS = ___` (recommended start: 500–1000 ms)

Spine MUST disable motion if keepalive traffic is absent for longer than the active hold timeout (Section 3).

---

## 10. Axis Table (v0.1) — Project-Filled

This section MUST list the axes Spine exposes in v0.1, their modes, units, and safe bounds.

Example format (replace with actual values):

| axis_id | name        | supports | unit_code |   min |   max |
| ------: | ----------- | -------- | --------- | ----: | ----: |
|       0 | drive_left  | velocity | m/s       | -0.50 | +0.50 |
|       1 | drive_right | velocity | m/s       | -0.50 | +0.50 |

---

## 11. Fault Codes (v0.1) — Project-Filled

This section MUST define at least the Stage 2 hardening faults.

Minimum recommended list:

* `CRC_HEADER_FAIL`
* `CRC_PAYLOAD_FAIL`
* `UNKNOWN_MSG_TYPE`
* `INVALID_AXIS_ID`
* `SETPOINT_OUT_OF_RANGE`
* `SESSION_INVALID`
* `KEEPALIVE_TIMEOUT`
* `INTERNAL_ERROR`

Each fault MUST specify: `fault_code`, severity, and whether motion is disabled.

---

## 12. Transport Notes (USB now, CAN later)

12.1 **USB (maintenance path)**
USB is an approved transport for this contract and MAY remain enabled as a maintenance/logging path indefinitely.

12.2 **CAN (future backbone)**
CAN SHALL carry the same canonical packets defined here. If fragmentation is required due to CAN frame size, fragmentation/reassembly MUST preserve the original packet bytes exactly before parsing under this contract.

---

## 13. Compliance

A Brain or Spine implementation is considered compliant with v0.1 if it:

* Produces and accepts packets per Section 5
* Implements safety invariants per Section 3
* Implements the required message types per Section 8 (ACK optional)
* Enforces timing per Section 9
* Publishes and respects the axis table per Section 10

---

If you paste this into your repo, the **only things you must fill** to make it “real” are:

1. the timing constants in Section 9
2. the axis table in Section 10
3. the fault code table in Section 11
4. the `magic` constant value (any fixed u16 you choose)

If you tell me your **current axes (even placeholders)** and whether you want **units to be normalized (-1..1) or physical (m/s, rad/s)**, I’ll fill Sections 10–11 in a strict v0.1 style that matches the rest of your project docs.
