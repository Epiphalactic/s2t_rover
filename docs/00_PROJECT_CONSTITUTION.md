
# Project Constitution v0.1

**Project Name:** Scout32 Distributed Research Rover  
**Status:** Canonical  
**Last Updated:** 2025-01-XX  

S2T (Scout to Titan) is the project identity and development arc, representing the deliberate progression from the initial Scout platform to the final Titan rover architecture.

---

## 1. Purpose (WHY)

This project exists to **build and evolve a research-grade, modular, six-wheel rover platform**  
(rocker-bogie / Mars-style suspension) for:

- Education
- Experimentation
- Portfolio-grade, self-directed learning

Domains explicitly in scope:

- Robotics
- Distributed systems
- Electronics
- Embedded software
- Autonomy (explicitly gated)

This platform is intended for **long-term use by the author and their child** as a shared learning and research system.

---

## 2. Non-Goals (What This Project Is Not)

This project is **explicitly not**:

- A commercial product
- Safety-certified or compliance-certified
- Intended for sale, deployment, or operational duty
- Optimized for mass production, cost minimization, or consumer usability
- An autonomous system by default
- Allowed to move independently without explicit human intent

**These exclusions are binding** and exist to prevent scope drift.

---

## 3. Hard Constraints (Boundaries)

The following constraints are **non-negotiable** unless explicitly revised:

### 3.1 Units & Scale
- **Units:** Metric (SI) only
- **Mechanical scale:** Defined by 6.5″ hoverboard hub motors

### 3.2 Power
- **Target end state:** ~10S Li-ion or LiPo  
  (exact implementation TBD)

### 3.3 Architecture
- **System type:** Distributed
- **Separation of concerns:** Mandatory

#### Compute Split
- **SBC (“Brain”)**
  - High-level logic
  - Planning
  - Orchestration
- **MCU (“Spine”)**
  - Real-time motor control
  - Sensor I/O
  - Reflex-level safety behaviors

### 3.4 Communication
- **Interconnect:**  
  CAN bus is the long-term embedded communication backbone

### 3.5 Control Philosophy
- Closed-loop control wherever applicable

### 3.6 Workflow
- Git-centric development (GitOps-style)

### 3.7 Code Quality (Binding)
Code must be:

- Readable
- Well-commented
- Human-understandable
- “Tasteful” in clarity, intent, and maintainability

> Cleverness without clarity is not acceptable.

### 3.8 Naming and Identity (Hard Constraint)

All components of this project—including hardware modules, sensors, firmware artifacts, telemetry fields, code identifiers, logs, and documentation—MUST follow the canonical naming rules defined in:

- `08_NAMING_CONVENTIONS.md`

Naming is treated as a **first-class architectural constraint**.

Hard rules:

- Names encode **identity**, not implementation
- Assigned identities are **immutable**
- Renaming in place is forbidden
- Supersession MUST occur via new identities, not overwriting
- Historical names MUST remain valid for interpretation of logs, data, and documentation

Any deviation from the naming conventions constitutes an architectural violation and MUST NOT be introduced without:
- An explicit update to the naming conventions document, and
- A corresponding entry in the Decision Log

Consistency of naming is required to preserve long-term clarity, safety, and learnability in a distributed system.

This includes Appendix A (Narrative vs Technical Terminology), which is binding and strictly enforced.


---

## 4. Invariants (Identity-Level Rules)

These rules define the **identity** of the system.  
Violating them means the project has become something else.

- The Brain must **not** depend on a specific motor technology  
  (brushed vs brushless is an implementation detail)
- The motion subsystem must be replaceable **without rewriting higher-level logic**
- The system must be modular:
  - Components can be added, removed, or replaced
- Modules should be discoverable and self-describing where practical
- Human-out-of-the-loop autonomy is:
  - Experimental only
  - Explicitly gated
- The system must:
  - Fail safely
  - Degrade predictably
- No hidden coupling
- No spaghetti architecture
- No undocumented “magic”

> If a decision matters, it must be written down.

---

## 5. Authority & Canon

- **Project files are authoritative**
- **Conversations are ephemeral and non-binding**

A decision exists **only if recorded** in:

- `02_DECISION_LOG.md`

Canonical document ownership:

- **Specifications:** `04_SPECS_AND_INTERFACES.md`
- **Ideas / experiments / ambitions:** `03_BACKLOG.md` (until promoted)

> If it is not written, it is not real.

Use of Large Language Models is governed by llms.txt, which defines how non-authoritative tools must interpret and operate within canonical project documents.

---

## 6. Update Protocol

Any change to **purpose, constraints, or invariants** requires:

- An explicit revision of this document

All proposed changes must be clearly labeled as one of:

- **Fact**
- **Proposal**
- **Experiment**

Rules:

- Conflicts must be flagged, not silently resolved
- Ambiguity must be surfaced, not assumed away

---

## 7. Design Ethos (Guiding Principle)

- Prefer clarity over cleverness
- Prefer interfaces over implementations
- Prefer systems that humans can reason about

Learning, maintainability, and understanding are **first-class requirements**.

---

_End of Constitution v0.1_
