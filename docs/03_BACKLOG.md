# Backlog v0.1

**Project:** Scout32 Distributed Research Rover  
**Status:** Active  
**Last Updated:** 2026-01-XX  
**Authority:** Project Constitution v0.1  

---

## How to Read This Backlog

This backlog contains **non-binding work items** only.

### Status Definitions
- **Planned** → Intended, but not yet implemented
- **Exploratory** → Allowed to be researched without commitment
- **Blocked** → Cannot proceed yet
- **Deferred** → Intentionally postponed
- **Done** → Completed and logged elsewhere
- **Ongoing** → Continuous hygiene activity

### Promotion Rules
Nothing in this file is binding until promoted to:

- **Decisions:** `02_DECISION_LOG.md`
- **Facts / Interfaces:** `04_SPECS_AND_INTERFACES.md`

---

## 1. Immediate / Foundation Work (Near-Term)

### B-001 — Resolve Power Integrity Issues
- **Status:** Done  
- **Priority:** Critical (Resolved)

**Description:**  
Eliminate SBC power throttling and establish clean, reliable power delivery.

**Acceptance Criteria:**
- `vcgencmd get_throttled` reports `0x0` under normal operation
- No brownouts during CPU load

---

### B-002 — Complete Pico SDK Setup
- **Status:** Done  
- **Priority:** High  

**Description:**  
Finish Pico SDK installation and confirm build toolchain.

---

### B-003 — Build First Spine Firmware Artifact
- **Status:** Done  
- **Priority:** High  

**Description:**  
Generate first `scout_spine.uf2` firmware image.

**Notes:**  
OLED rendering verified as Spine-local.

---

### B-004 — Minimal Brain ↔ Spine Communication Stub
- **Status:** Done  
- **Priority:** High  

**Description:**  
Implement a minimal, non-CAN communication path for early validation.

**Notes:**  
Completed via Brain-driven build/flash/control workflow over USB/SSH.  
Runtime packet semantics are handled under B-013 and beyond.

---

## 2. Architecture & Interfaces

### B-010 — Brain–Spine Interface Contract
- **Status:** Done  
- **Priority:** High  

**Description:**  
Define and adopt a minimal, explicit interface between Brain and Spine.

**Notes:**  
Adopted as `BRAIN_SPINE_MESSAGE_CONTRACT.md` v0.2.  
Spine-side protocol stack implemented and frozen (see Decision Log D-016).

---

### B-011 — Coding Standards & Style Guide
- **Status:** Done  
- **Priority:** Medium  

**Description:**  
Formalize readability, commenting, and “taste” expectations.

---

### B-012 — Module Identity & Discovery Philosophy
- **Status:** Exploratory  
- **Priority:** Medium  

**Description:**  
Explore how modules identify themselves on the bus.

---

### B-013 — Spine Transport Adapter (USB Serial)
- **Status:** Planned  
- **Priority:** High  

**Description:**  
Wire a concrete transport into the Spine protocol framer.

**Acceptance Criteria:**
- Bytes received from USB are fed into `proto_framer`
- Only validated packets reach higher logic

---

### B-014 — Packet Dispatcher Stub
- **Status:** Planned  
- **Priority:** High  

**Description:**  
Introduce a minimal dispatcher that routes validated packets by message type.

**Notes:**  
No behavioral semantics beyond routing.

---

### B-015 — Spine State Machine (INIT / SAFE / ENABLED / FAULT)
- **Status:** Planned  
- **Priority:** High  

**Description:**  
Implement the Spine state model defined in the protocol contract.

---

### B-016 — Fault Injection & Safety Verification
- **Status:** Planned  
- **Priority:** High  

**Description:**  
Deliberately inject protocol faults and verify correct safety behavior.

---

### B-017 — Brain-Side Protocol Mirror
- **Status:** Planned  
- **Priority:** Medium  

**Description:**  
Implement a Brain-side version of the protocol stack for testing and tooling.

---

## 3. Power & Motion Subsystems

### B-020 — Power Architecture Definition
- **Status:** Exploratory  
- **Priority:** High  

---

### B-021 — Hoverboard Hub Motor Integration Study
- **Status:** Exploratory  
- **Priority:** Medium  

---

### B-022 — Motor Controller Evaluation
- **Status:** Exploratory  
- **Priority:** Medium  

---

## 4. Communication & CAN Bus

### B-030 — CAN Bus Design Philosophy
- **Status:** Planned  
- **Priority:** Medium  

---

### B-031 — CAN Physical Layer Options
- **Status:** Exploratory  
- **Priority:** Low  

---

## 5. Sensors & Perception

### B-040 — Sensor Module Taxonomy
- **Status:** Exploratory  
- **Priority:** Low  

---

### B-041 — Closed-Loop Feedback Strategy
- **Status:** Exploratory  
- **Priority:** Medium  

---

## 6. Autonomy & Control (Explicitly Gated)

### B-050 — Human-in-the-Loop Control Baseline
- **Status:** Planned  
- **Priority:** Medium  

---

### B-051 — Autonomy Experiments (Sandboxed)
- **Status:** Deferred  
- **Priority:** Low  

---

## 7. Documentation & Learning

### B-060 — System Architecture Diagram
- **Status:** Planned  
- **Priority:** Medium  

---

### B-061 — “Why This Exists” Narrative
- **Status:** Planned  
- **Priority:** Low  

---

## 8. Risk & Hygiene

### B-070 — Power & Thermal Risk Analysis
- **Status:** Planned  
- **Priority:** Medium  

---

### B-071 — Scope Creep Monitoring
- **Status:** Ongoing  
- **Priority:** Medium  

---

## 9. Parking Lot (Explicitly Non-Binding)

The following ideas are acknowledged but carry **no architectural weight**:

- Advanced autonomy stacks
- Swarm coordination
- High-redundancy safety systems
- External payload ecosystems

---

_End of Backlog v0.1_
