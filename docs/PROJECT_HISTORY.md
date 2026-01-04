# Project History & Progress Log

**Project:** Scout32 / Titan Rover (S2T Rover)  
**Status:** Living historical record (non-authoritative)  
**Authority:** Informational only — does NOT override canonical documents  

> This document is non-canonical unless explicitly referenced by a canonical document.  
> In case of conflict, the Project Constitution, Context Pack, Specs, and Decision Log prevail.

---

## 1. Purpose

This document provides a **chronological, narrative record** of what was done, when, and why.

It is explicitly **not**:
- A source of binding truth
- A specification
- A decision authority

Its role is to:
- Preserve human-readable project memory
- Reduce cognitive load after time gaps
- Help future readers (including future maintainers) understand project evolution
- Act as a bridge between ephemeral chats and formal canon

---

## 2. Relationship to Canon

| Document | Role |
|--------|------|
| Project Constitution | Identity, invariants, non-negotiables |
| Context Pack | Current authoritative snapshot |
| Decision Log | Binding architectural decisions |
| Specs & Interfaces | Technical contracts and interfaces |
| **Project History (this doc)** | Narrative timeline only |

Rules:
- Nothing becomes real because it is written here
- This document may reference canon but must not redefine it
- Canonical documents always win on conflict

---

## 3. Entry Format (Required)

Each entry MUST follow this structure exactly:

### YYYY-MM-DD — Short descriptive title

**What was done:**
- Factual actions taken

**Why it mattered:**
- Brief rationale or learning

**Canon impact:**
- None  
- Context Pack updated  
- Decision Log entry  
- Specs updated  

(choose all that apply)

**Next planned step:**
- One concrete, immediate next action


---

## 4. Project Timeline

### 2026-01-02 — Spine OLED Verified (Spine-Local) and Canon Reconciliation

**What was done:**
- Verified current Spine firmware builds, flashes, and boots reliably
- Confirmed OLED display is driven locally by the Spine firmware
- Verified Pico SDK + CMake toolchain produces deterministic `.uf2` artifacts
- Corrected earlier misstatement that implied Brain-driven OLED output
- Reconciled Context Pack and Backlog to reflect accurate current state

**Why it mattered:**
- Eliminated ambiguity between tooling experiments and actual firmware behavior
- Prevented accidental over-claiming of Brain ↔ Spine integration
- Restored alignment between observed behavior and canonical documentation

**Canon impact:**
- Context Pack updated (Current Snapshot corrected)
- Backlog statuses reconciled
- No Decision Log entry required

**Next planned step:**
- Implement and verify Brain ↔ Spine Contract v0.1 packet framing and Spine-side safety invariants

---

### 2026-01-02 — Documentation Hygiene and Process Formalization

**What was done:**
- Introduced non-canonical Project History document
- Clarified authority boundaries across Constitution, Context Pack, History, and Decision Log
- Updated Risk Register to reflect mitigated power instability
- Added reconciliation and close-out rules to Process Log

**Why it mattered:**
- Reduced likelihood of future documentation drift
- Made reconciliation after missed updates straightforward
- Established a repeatable, low-friction documentation workflow

**Canon impact:**
- Process and Risk documents updated
- No architectural or binding decisions introduced

**Next planned step:**
- Perform full document consistency audit (Step 4 completion)
- Proceed to Brain ↔ Spine Contract reconciliation (Step 5)

---
### 2026-01-02 — Project History Canon Clarified and Unified

**What was done:**
- Identified that `06_RULES_AND_PROCESS_LOG.md` contained a section labeled “Project History”
- Determined that this section was procedural, not a chronological record
- Established `PROJECT_HISTORY.md` as the single, authoritative chronological history document
- Updated Rules & Process documentation to reference `PROJECT_HISTORY.md` instead of duplicating history

**Why it mattered:**
- Prevented the existence of multiple competing “history” sources
- Eliminated a potential long-term drift vector where narrative could be misinterpreted as authority
- Clarified the separation between process rules and historical record

**Canon impact:**
- Rules & Process Log updated to point to `PROJECT_HISTORY.md`
- No Decision Log entry required

**Next planned step:**
- Continue document-by-document consistency audit (Step 4)



## 2026-01-XX — Stage 2 / Step 1 Completed: Spine Protocol Stack Hardening

### Summary
Stage 2, Step 1 of the S2T project has been completed.  
This step focused exclusively on **hardening the Brain ↔ Spine protocol infrastructure** on the Spine (MCU) side, prior to transport wiring or behavioral state machines.

The result is a complete, deterministic, and testable protocol ingestion pipeline capable of safely accepting raw byte streams and emitting fully validated packets.

---

### Scope of Work Completed

The following protocol components were implemented on Spine:

- **Wire-format constants**
  - Fixed header/trailer sizes
  - Field offsets
  - Payload size caps

- **CRC implementations**
  - CRC-16/CCITT-FALSE for header integrity
  - CRC-32/ISO-HDLC for payload integrity
  - Exact alignment with Brain ↔ Spine Message Contract v0.2

- **Header parsing and validation**
  - Little-endian deserialization
  - Magic and version enforcement
  - Header CRC verification
  - Payload length bounds checking

- **Full packet validation**
  - Header validation
  - Total packet length verification
  - Payload CRC verification
  - Safe handling of zero-length payloads

- **Stream framer / resynchronizer**
  - Bounded internal buffer
  - Byte-by-byte ingestion
  - Magic-based resynchronization
  - Header-first validation to determine expected length
  - Single-byte discard strategy on corruption
  - Diagnostic counters for dropped bytes, header errors, packet errors, and successful packets

This establishes the canonical pipeline:


---

*(Add new entries above this line)*

---

_End of Project History_

