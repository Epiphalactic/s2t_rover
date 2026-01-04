# Context Pack v0.1

**Project:** Scout32 Distributed Research Rover  
**Status:** Active  
**Canonical Authority:** Project Constitution v0.1  

---

## 1. Objective (Current Framing)

Establish a **stable, professional-grade distributed robotics platform** that:

- Separates high-level cognition from real-time control
- Supports modular growth over time
- Serves as a long-term learning and research system

**Current phase priority:**  
Architecture correctness, tooling, and system hygiene  
**over** feature completeness.

---

## 2. Current Snapshot (Authoritative State)

This section represents the **current operational truth** of the project.  
It is updated **only when the present state changes**.

- **Phase:** Stage 2 — Infrastructure Hardening
- **Power:** Stable; Raspberry Pi operates without throttling under load
- **Spine firmware:** Builds, flashes, and boots reliably; OLED operational (Spine-local display)
- **Brain ↔ Spine protocol stack:** Implemented and building on Spine
  - Wire-format constants
  - CRC-16 (header) and CRC-32 (payload) per contract v0.2
  - Header parsing and validation
  - Full packet validation
  - Stream framer with resynchronization and bounded buffering
- **Brain ↔ Spine transport:** Not yet wired into Spine runtime (USB/CAN adapters pending)
- **Motion:** Not implemented; Spine remains SAFE-by-default
- **Primary blockers:** None
- **Next gating milestone:**  
  Wire validated byte streams into the Spine protocol framer and enforce behavior via state machine logic

**Evidence:**
- Spine protocol stack compiles and links into `scout_spine`
- Pico SDK + CMake build produces working `.uf2`
- Stream framer validated via clean builds and integration
- Power stability verified under load

---

## 3. System Architecture (Current)

### 3.1 Brain — Titan (SBC)

- **Hardware:** Raspberry Pi (Titan)
- **OS:** Headless Raspberry Pi OS (Lite)

**Responsibilities:**
- High-level logic and orchestration
- Human interface (SSH, tooling)
- Build system and deployment
- Future protocol packet generation and validation (Brain-side mirror)

---

### 3.2 Spine — Scout (MCU)

- **Hardware:** RP2040 (Raspberry Pi Pico)

**Responsibilities:**
- Deterministic real-time control
- Safety enforcement (SAFE-by-default, silence=stop)
- Hardware abstraction
- Protocol ingestion, framing, and validation

---

## 4. Software & Tooling Status

- Git repository initialized and in active use
- Secure SSH access verified
- Pico SDK installed and functional
- Deterministic Spine firmware build and flash process verified
- Spine-side protocol stack implemented and integrated
- Brain-side serial tooling available for development and diagnostics

---

## 5. What Is Explicitly *Not* Decided Yet

The following items remain intentionally open:

- Final power architecture
- Motor controller selection
- CAN physical-layer details
- Sensor suite composition
- Autonomy behaviors
- Message dispatch semantics beyond validation

Silent assumptions are forbidden.

---

## 6. Immediate Focus (Stage 2)

The immediate focus is to:

1. Wire a transport adapter (USB serial initially) into the Spine protocol framer
2. Introduce a minimal packet dispatcher stub (no semantics beyond routing)
3. Implement the Spine state machine (INIT / SAFE / ENABLED / FAULT)
4. Enforce and verify safety behavior via fault-injection tests

No motion, autonomy, or feature expansion is permitted until these are complete.

---

## 7. Chronological Record

For a detailed timeline of work completed and rationale, see:

- `PROJECT_HISTORY.md`

---

_End of Context Pack v0.1_
