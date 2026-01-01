# Specs & Interfaces v0.1

**Project:** Scout32 Distributed Research Rover  
**Status:** Canonical (Foundational)  
**Last Updated:** 2025-01-XX  
**Authority:** Project Constitution v0.1  

---

## 0. Scope of This Document

This document defines **technical facts, interfaces, and constraints** that all other work must obey.

It intentionally does **not** define:
- Final implementations
- Component selections (unless already binding)
- Optimizations
- Aspirational or future features

> If something is uncertain, speculative, or aspirational, it does **not** belong here yet.

---

## 1. Units & Conventions (Binding)

The following conventions are **mandatory**:

- **All measurements:** Metric (SI)
- **Angles:**
  - Radians internally
  - Degrees allowed for human-facing output
- **Time:**
  - Seconds (`s`)
  - Milliseconds (`ms`)
  - Microseconds (`µs`)
- **Voltage notation:**
  - Nominal voltage stated explicitly (e.g., `10S nominal`)

### Coordinate Frames
- Defined explicitly per subsystem
- No assumed global frame exists yet

---

## 2. System-Level Architecture (Fact)

### 2.1 Node Roles

#### Titan — Brain (SBC)

- **Class:** Single-board computer  
- **OS:** Linux (headless)

**Responsibilities:**
- High-level logic and orchestration
- Planning and decision-making
- Build system and deployment
- Human interface (SSH, tooling)
- Version control integration

**Timing Characteristics:**
- Non-real-time
- Best-effort scheduling

---

#### Scout — Spine (MCU)

- **Class:** Microcontroller

**Responsibilities:**
- Deterministic, real-time tasks
- Motor control
- Sensor acquisition
- Safety reflexes

**Timing Characteristics:**
- Hard or near-hard real-time
- Deterministic execution required

---

## 3. Responsibility Boundary (Hard Interface)

The following boundary is **binding**:

| Function               | Brain (SBC) | Spine (MCU) |
|------------------------|-------------|-------------|
| High-level planning    | ✔           | ✖           |
| Motor commutation      | ✖           | ✔           |
| Control loops          | ✖           | ✔           |
| Sensor polling         | ✖           | ✔           |
| Safety cutoffs         | ✖           | ✔           |
| State aggregation      | ✔           | ✔           |
| Logging                | ✔           | Optional    |

**Hard rules:**
- The Brain never directly drives hardware
- The Spine never makes mission-level decisions

---

## 4. Motion Subsystem Abstraction (Invariant Interface)

### 4.1 Motion Independence

The Brain must **not** depend on:
- Brushed vs brushless motors
- Specific motor controllers
- Wheel geometry details

These are implementation details owned by the motion subsystem.

---

### 4.2 Required Motion Interface (Conceptual)

At minimum, the motion subsystem must expose:

- Desired velocity or torque command
- Current measured velocity
- Fault / status flags
- Enable / disable control

> No kinematic assumptions are made at this layer.

---

## 5. Communication Philosophy

### 5.1 Transport Layers

- **Early development:**  
  Temporary transports allowed (USB, UART, etc.)
- **Long-term embedded backbone:**  
  CAN bus

> Transport may change; **message semantics must not**.

---

### 5.2 Messaging Principles

- Explicit message definitions
- No hidden side effects
- Deterministic parsing
- Versioned message formats
- Backward compatibility where feasible

---

## 6. CAN Bus (Reserved, Not Finalized)

### 6.1 Intent

CAN is intended to serve as:
- Deterministic embedded network
- Module interconnect
- Fault-tolerant communication layer

---

### 6.2 Explicitly Open (Not Yet Defined)

The following **must not be assumed** until specified:

- Bitrate
- Physical transceivers
- Arbitration strategy
- Addressing scheme

---

## 7. Module Philosophy (Binding)

Modules must be:
- Replaceable
- Isolated
- Clearly owned

A module:
- Has a defined interface
- Owns its hardware
- Reports its state

Self-identification is **desired** but not yet specified.

---

## 8. Power Domains (Partial, Binding Where Stated)

### 8.1 Known Facts

- Final system target: ~10S Li-ion or LiPo
- Multiple voltage domains are expected
- Power integrity is critical for SBC stability

---

### 8.2 Explicit Unknowns

- Final rail voltages
- Distribution topology
- Protection mechanisms

> No subsystem may assume a specific voltage unless explicitly documented.

---

## 9. Safety Interfaces (Binding Philosophy)

The Spine has authority to:
- Disable motion
- Enter safe states

Safety actions must:
- Be deterministic
- Be local
- Not depend on SBC availability

---

## 10. Software Interfaces & Style (Binding)

### 10.1 Language Roles

- **Python:** High-level logic and orchestration
- **C / C++:** Real-time, embedded control

---

### 10.2 Code Requirements

Code must exhibit:
- Clear intent
- Heavy commentary where reasoning matters
- No “magic numbers” without explanation
- Readability over cleverness

> Code is a teaching artifact as well as a functional one.

---

## 11. Logging & Observability (Minimal Requirement)

Subsystems must expose:
- State
- Errors
- Faults

Logging format and transport are **not yet fixed**.

> Silent failure is forbidden.

---

## 12. Versioning & Compatibility

- Interfaces must be versioned
- Breaking changes require:
  - Documentation
  - Decision Log entry
- Temporary hacks must be labeled as such

---

## 13. What Does *Not* Belong Here (Reminder)

This document must not include:
- Feature wishlists
- Future autonomy plans
- Hypothetical sensors
- Unverified assumptions

Those belong in the **Backlog**.

---

## 14. Open Specification Questions

- Minimum Brain ↔ Spine message set?
- Required timing guarantees?
- Module discovery mechanism?
- Fault escalation strategy?

These guide future revisions but are **not constraints yet**.

---

_End of Specs & Interfaces v0.1_
