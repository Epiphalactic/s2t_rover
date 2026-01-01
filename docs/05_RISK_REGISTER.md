# Risk Register v0.1

**Project:** Scout32 Distributed Research Rover  
**Status:** Active  
**Last Updated:** 2025-01-XX  
**Authority:** Project Constitution v0.1  

---

## How to Use This Document

This is **not** a list of fears.  
It is a list of **credible failure modes**.

Principles:
- Risks are allowed to exist; silence is not
- Mitigations reduce risk; they do not eliminate it
- This document evolves as understanding improves

If a risk materializes, it must be:
- Acknowledged
- Logged
- Addressed deliberately

---

## Risk Scoring Legend (Informal)

- **Likelihood:** Low / Medium / High
- **Impact:** Low / Medium / High
- **Priority:** Derived from judgment, not math

> This is a thinking tool, not a compliance artifact.

---

## 1. Power & Electrical Risks

### R-001 — Unstable Power Delivery to SBC
- **Likelihood:** High  
- **Impact:** High  
- **Priority:** Critical  

**Description:**  
Insufficient or noisy power delivery causes SBC throttling, instability, or data corruption.

**Evidence:**  
Observed throttling (`vcgencmd get_throttled → 0x50005`).

**Mitigation Strategy:**
- Improve power source and regulation
- Validate under load
- Treat clean power as a gating requirement

**Status:** Open (Active Blocker)

---

### R-002 — High-Voltage Battery Hazards (10S)
- **Likelihood:** Medium  
- **Impact:** High  
- **Priority:** High  

**Description:**  
10S Li-ion / LiPo introduces risks of short-circuit, overcurrent, and thermal events.

**Mitigation Strategy:**
- Conservative design margins
- Clear voltage-domain separation
- Fusing and protection before final integration

**Status:** Open (Design Phase)

---

## 2. Motion & Actuation Risks

### R-010 — Brushless Hub Motor Control Complexity
- **Likelihood:** Medium  
- **Impact:** High  
- **Priority:** High  

**Description:**  
Hoverboard hub motors require complex control and may impose architectural constraints.

**Mitigation Strategy:**
- Keep motion subsystem abstracted
- Allow controller replacement without system-wide impact
- Prototype before committing

**Status:** Open (Exploratory)

---

### R-011 — Mechanical Load & Thermal Stress
- **Likelihood:** Medium  
- **Impact:** Medium  
- **Priority:** Medium  

**Description:**  
Weight, terrain, and duty cycle may exceed assumptions, stressing motors and structure.

**Mitigation Strategy:**
- Conservative early operation
- Instrumentation and monitoring
- Iterative mechanical refinement

**Status:** Open

---

## 3. Architecture & Software Risks

### R-020 — Boundary Erosion Between Brain and Spine
- **Likelihood:** Medium  
- **Impact:** High  
- **Priority:** High  

**Description:**  
Gradual leakage of responsibilities causes spaghetti architecture and tight coupling.

**Mitigation Strategy:**
- Explicit interface contracts
- Enforce responsibility table
- Reject convenience-driven shortcuts

**Status:** Open

---

### R-021 — Hidden Assumptions in Interfaces
- **Likelihood:** Medium  
- **Impact:** Medium  
- **Priority:** Medium  

**Description:**  
Implicit assumptions (timing, units, ranges) cause subtle, hard-to-diagnose bugs.

**Mitigation Strategy:**
- Explicit specifications
- Versioned interfaces
- Defensive parsing

**Status:** Open

---

### R-022 — Premature Optimization
- **Likelihood:** Medium  
- **Impact:** Medium  
- **Priority:** Medium  

**Description:**  
Early optimization of performance or architecture introduces fragility.

**Mitigation Strategy:**
- Prioritize clarity and correctness
- Defer optimization
- Label experiments clearly

**Status:** Open

---

## 4. Communication & CAN Bus Risks

### R-030 — CAN Bus Overcommitment
- **Likelihood:** Low  
- **Impact:** Medium  
- **Priority:** Medium  

**Description:**  
Prematurely locking CAN details limits architectural flexibility.

**Mitigation Strategy:**
- Separate message semantics from transport
- Delay physical-layer commitment

**Status:** Open

---

### R-031 — Debugging Complexity in Distributed Systems
- **Likelihood:** High  
- **Impact:** Medium  
- **Priority:** High  

**Description:**  
Distributed nodes complicate fault isolation and debugging.

**Mitigation Strategy:**
- Strong logging
- Clear ownership of faults
- Simple initial topologies

**Status:** Open

---

## 5. Autonomy & Safety Risks

### R-040 — Unintended Motion
- **Likelihood:** Low  
- **Impact:** High  
- **Priority:** High  

**Description:**  
Software error causes motion without explicit human intent.

**Mitigation Strategy:**
- Default motion gating
- Explicit enable semantics
- Local Spine authority for disable

**Status:** Open (Gated by Design)

---

### R-041 — Overconfidence in Experimental Autonomy
- **Likelihood:** Medium  
- **Impact:** Medium  
- **Priority:** Medium  

**Description:**  
Experimental autonomy may be trusted beyond its maturity.

**Mitigation Strategy:**
- Sandbox experiments
- Explicit labeling
- Human-in-the-loop by default

**Status:** Open

---

## 6. Process & Scope Risks

### R-050 — Scope Creep
- **Likelihood:** High  
- **Impact:** Medium  
- **Priority:** High  

**Description:**  
Interesting ideas dilute focus and destabilize architecture.

**Mitigation Strategy:**
- Backlog discipline
- Constitution enforcement
- Regular scope review

**Status:** Ongoing

---

### R-051 — Documentation Drift
- **Likelihood:** Medium  
- **Impact:** Medium  
- **Priority:** Medium  

**Description:**  
Reality diverges from written documents.

**Mitigation Strategy:**
- Treat documents as authority
- Update docs when behavior changes

**Status:** Open

---

## 7. Learning & Human Factors

### R-060 — Burnout / Cognitive Overload
- **Likelihood:** Medium  
- **Impact:** Medium  
- **Priority:** Medium  

**Description:**  
Project complexity overwhelms learning intent.

**Mitigation Strategy:**
- Incremental goals
- Celebrate subsystem wins
- Avoid constant large refactors

**Status:** Open

---

### R-061 — Loss of Teaching Clarity
- **Likelihood:** Medium  
- **Impact:** Medium  
- **Priority:** Medium  

**Description:**  
Code and architecture become hard to reason about for humans.

**Mitigation Strategy:**
- Enforce the “taste” rule
- Heavy commentary
- Prefer boring solutions

**Status:** Open

---

## 8. Accepted Risks (Conscious Tradeoffs)

The following risks are **accepted by design**:

- System is not safety-certified
- System may fail in non-catastrophic ways
- Learning value outweighs robustness in early phases

These are not failures.  
They are **choices**.

---

## 9. Review Cadence

Revisit this document:
- After major architectural changes
- After incidents
- At major iteration milestones

---

_End of Risk Register v0.1_
