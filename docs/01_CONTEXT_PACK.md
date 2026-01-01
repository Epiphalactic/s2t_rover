# Context Pack v0.1

**Project:** Scout32 Distributed Research Rover  
**Status:** Active  
**Last Updated:** 2025-01-XX  
**Canonical Authority:** Project Constitution v0.1  

---

## 1. Objective (Current Framing)

Establish a **stable, professional-grade distributed robotics platform** that:

- Separates high-level cognition from real-time control
- Supports modular growth over time
- Serves as a long-term learning and research system

Primary learning domains:

- Embedded systems
- Robotics
- Distributed architectures
- Autonomy (explicitly gated)

**Current phase priority:**  
Architecture correctness, tooling, and system hygiene  
**over** feature completeness.

---

## 2. System Architecture (Current)

### 2.1 Brain–Spine Model

#### Titan — Brain (SBC)

- **Hardware:** Raspberry Pi 3B
- **OS:** Headless Linux node

**Responsibilities:**
- High-level logic
- Planning and orchestration
- GitOps workflow
- Build tooling
- Human interface (SSH, development tools)

---

#### Scout — Spine (MCU)

- **Hardware:** RP2040 Pico (temporary / initial MCU)

**Responsibilities:**
- Real-time motor control
- Sensor I/O
- Deterministic timing
- “Reflex”-level behaviors

---

### 2.2 Architectural Philosophy

- Python handles **thinking**
- C / C++ handles **reflexes**
- No hard coupling between logic and hardware implementation
- Motion subsystem is abstracted from cognition

---

## 3. Mechanical Baseline

- Platform derived from **Scout32 ESP32 rover** (Thingiverse)
- Six-wheel configuration
- Rocker-bogie / Mars-style suspension intent
- Final scale constrained by **6.5″ hoverboard hub motors**

**Status:**
- Mechanical design is mutable
- Mechanical design is **not yet canonical**

---

## 4. Power Status

- **Final target:** ~10S Li-ion or LiPo

### Current State
- Power integrity issues observed
- Raspberry Pi reports throttling  
  (`vcgencmd get_throttled → 0x50005`)
- Power subsystem is currently the **primary blocker**

**Not yet committed:**
- Final power architecture
- Rail topology
- Protection strategy

---

## 5. Software & Tooling Status

### 5.1 GitOps

- Git repository initialized
- Remote hosted on GitHub
- ED25519 SSH keys generated and verified
- Secure push/pull operational

> The repository is considered the **“soul” of the project**.

---

### 5.2 Development Environment

- VS Code integrated with Raspberry Pi
- ARM toolchain installed
- CMake installed
- Pico SDK **not yet fully downloaded / built**

---

### 5.3 Access & Identity

- Headless operation confirmed
- SSH access functional
- Hostname established: `titan.local`
- User account established and verified

---

## 6. What Is Already Decided (Binding)

The following are **binding** decisions:

- Brain–Spine architectural split
- Distributed system approach
- Git-centric workflow
- Readable, heavily commented, “tasteful” code
- Metric units only
- Modular system philosophy
- CAN bus planned as long-term embedded backbone

---

## 7. What Is Explicitly *Not* Decided Yet

The following items are **intentionally open** and must not be assumed:

- Final power distribution design
- Final motor controller selection
- CAN bus physical-layer implementation details
- Sensor suite composition
- Autonomy level and behaviors
- Redundancy depth and strategy

> These are open by design. Silent assumptions are forbidden.

---

## 8. Immediate Blockers

- Unclean power delivery to Raspberry Pi
- Pico SDK setup incomplete
- No compiled firmware artifact yet (`.uf2`)

---

## 9. Next Actions (Near-Term)

Ordered by priority:

1. Resolve power integrity issues  
   *(target: `vcgencmd get_throttled → 0x0`)*
2. Complete Pico SDK installation
3. Build first firmware artifact (`scout_spine.uf2`)
4. Establish minimal Brain ↔ Spine communication (even stubbed)
5. Log first formal decision in the Decision Log

---

## 10. Open Questions

These guide future work but are **not constraints** yet:

- What minimum Brain ↔ Spine interface contract is required?
- What voltage domains will exist in v1 power architecture?
- What guarantees are required from the motion layer?
- How will modules identify themselves over the bus?

---

## 11. Success Criteria (Current Phase)

Success for this phase is defined as:

- Clean, repeatable builds
- Deterministic MCU firmware flashing
- Stable SBC operation under load
- Clear separation of responsibilities
- Incremental progress without architectural debt

---

## 12. Glossary

- **Titan:** SBC “Brain” node (Raspberry Pi)
- **Scout:** MCU “Spine” node (RP2040)
- **Brain–Spine:** Architecture separating cognition from reflexes
- **GitOps:** Git-driven development and deployment workflow

---

## 13. Project Naming & Path

- **Scout** refers to the Scout32 ESP32 rover from Thingiverse  
  (initial chassis and starting point)
- **Titan** refers to the final, evolved rover:
  - Six-wheeled
  - Brushless
  - Advanced
  - Autonomous (explicitly gated)

**Scout → Titan** is the journey.

**Project name:** `s2trover`

---

_End of Context Pack v0.1_
