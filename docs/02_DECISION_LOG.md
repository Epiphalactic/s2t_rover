# Decision Log

> **IMPORTANT — HISTORICAL RECORD**
>
> This document is a **historical record of decisions** made during the evolution of the project.
> It must be treated as **reference material only**.
>
> No inference about current system behavior, architecture, or intent should be made
> unless a statement is **explicitly marked as active and authoritative**.
>
> The **only authoritative truth** is found in:
> - The Project Constitution
> - The Context Pack
> - The active Specifications & Interfaces
>
> This log exists to preserve *why* decisions were made, not to redefine *what is true now*.





## Supersession Conventions

- **Superseded information MUST remain visible** for historical traceability.
- Superseded text SHALL be struck through using Markdown strikethrough (`~~like this~~`).
- Any superseding or corrective text SHALL be written in *italics* immediately following.
- Deletions without trace are forbidden.

This ensures future readers can understand **what was believed at the time** and **why it changed**.
### D-014 — Brain Drives OLED Display (Initial Assumption)

**Date:** 2026-01-01

**Decision:**
~~The Brain (Raspberry Pi) will directly drive the OLED display on the Spine via USB.~~

*Corrected: The OLED display is driven locally by the Spine firmware.
The Brain does not currently drive the display; previous assumption was incorrect.*

**Context:**
Initial testing conflated Spine-local rendering with Brain-driven output.

**Rationale:**
Early observability tests focused on confirming OLED functionality,
not on validating data origin.

**Consequences / Tradeoffs:**
- No functional regression
- Documentation required reconciliation

**Revisit Conditions:**
None. Entry retained for historical accuracy.




### D-015 — Adopt Brain ↔ Spine Message Contract v0.1 (Normative)

**Date:** 2026-01-02

**Decision:**  
The document `BRAIN_SPINE_MESSAGE_CONTRACT.md` is formally adopted as the **normative and authoritative** Brain ↔ Spine interface specification for **Stage 2 — Infrastructure Hardening**.

This adoption freezes the contract at **v0.1** with no remaining undefined fields.

**Scope:**  
This decision makes the following binding for Stage 2:

- Packet structure (header, payload, trailer)
- Protocol versioning rules
- Spine state model
- Safety invariants (SAFE-by-default, silence=stop)
- Keepalive definition
- Timing constants
- Axis table
- Fault code table

**Rationale:**  
Stage 2 requires a stable, transport-agnostic, and testable interface that enforces safety **locally on the Spine**, independent of Brain correctness or availability.  
Making the contract normative eliminates hidden coupling, undocumented assumptions, and architecture drift before motion or CAN integration begins.

**Consequences / Tradeoffs:**

- All Brain ↔ Spine communication MUST conform to this contract
- Any deviation requires:
  - A protocol version change, and
  - A new Decision Log entry
- Transport remains swappable (USB now; CAN later) without semantic change
- Motion and autonomy work remain gated until contract compliance is proven

**Revisit Conditions:**  
Only when:
- Exiting Stage 2, or
- Introducing protocol version v0.2 or later

This decision remains binding until explicitly superseded.



### D-016 — Define CRC Variants and Bump Protocol to v0.2

**Date:** 2026-01-03

**Decision:**
The Brain ↔ Spine protocol is bumped from v0.1 to v0.2 to explicitly define CRC variants:

- `header_crc16`: CRC-16/CCITT-FALSE (poly 0x1021, init 0xFFFF, refin/refout false, xorout 0x0000)
- `payload_crc32`: CRC-32/ISO-HDLC (poly 0x04C11DB7, init 0xFFFFFFFF, refin/refout true, xorout 0xFFFFFFFF)

**Rationale:**
“CRC-16” and “CRC-32” are ambiguous without variant parameters. Explicit definitions prevent mismatched implementations and ensure interoperability across languages and platforms.

**Consequences / Tradeoffs:**
- Any implementation using different CRC variants is non-compliant.
- Receivers MAY reject higher `proto_minor` per the contract’s compatibility rules.

**Revisit Conditions:**
Only when introducing v0.3+.


## D-016 — Adopt Brain ↔ Spine Message Contract v0.2 and Freeze Spine Protocol Stack

**Date:** 2026-01-XX  
**Status:** Adopted  
**Applies to:** Stage 2 — Infrastructure Hardening

### Decision

The document `BRAIN_SPINE_MESSAGE_CONTRACT.md` v0.2 is adopted as the
authoritative and normative specification for Brain ↔ Spine communication.

The Spine-side protocol ingestion stack implementing this contract is
considered complete for Stage 2 / Step 1 and is frozen as authoritative.

### Scope

This decision formally adopts and freezes the following on Spine:

- Packet wire format (header, payload, trailer)
- Protocol magic and versioning rules
- CRC algorithms and parameters:
  - CRC-16/CCITT-FALSE for header integrity
  - CRC-32/ISO-HDLC for payload integrity
- Header parsing and validation rules
- Full packet validation rules
- Stream framing and resynchronization behavior

The following files are authoritative for protocol handling on Spine:

- `proto_constants.h`
- `proto_crc.h` / `.cpp`
- `proto_header.h` / `.cpp`
- `proto_packet.h` / `.cpp`
- `proto_framer.h` / `.cpp`

### Rationale

Explicitly freezing the protocol stack at this stage ensures:

- Safety invariants cannot be bypassed by transport wiring
- All future behavior operates on validated inputs
- Brain-side and Spine-side implementations can be tested for equivalence
- Future contributors and LLMs do not reimplement or diverge from protocol logic

This decision intentionally precedes transport integration and state-machine
implementation to enforce correctness-first architecture.

### Non-Goals

This decision does NOT adopt or implement:

- Transport adapters (USB, UART, CAN)
- Message dispatch semantics
- Spine state machine logic
- Motion control or actuation
- Brain-side protocol mirror
- Automated test harnesses

These items remain planned and are tracked in the backlog.

### Consequences

- Any change to protocol behavior requires:
  - A protocol version change, and
  - A new Decision Log entry
- Parallel or alternate protocol implementations are prohibited
- All future Spine-side message handling MUST consume validated packets
  produced by the framer and validators defined above


---

_End of Decision Log_

If a decision appears to conflict with current project state,
refer to the **Context Pack** for the authoritative snapshot.
