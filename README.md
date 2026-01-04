# Scout32 Distributed Research Rover (S2T — Scout to Titan)

This repository contains Scout32, a distributed research rover project
developed under the S2T (Scout to Titan) program.

S2T represents both the project identity and the long-term development arc:
the deliberate evolution from early Scout platforms toward the final Titan
rover architecture.

This is a learning and research system, not a product.

----------------------------------------------------------------

PROJECT PURPOSE

Scout32 exists to build and evolve a research-grade, modular rover platform
with a strong emphasis on:

- Architecture correctness
- Safety-first design
- Human understanding and teachability
- Long-term experimentation and iteration

Domains explicitly in scope include:

- Robotics
- Distributed systems
- Electronics
- Embedded software
- Autonomy (explicitly gated and experimental)

The platform is intended for long-term educational use by the author and
their child, and is developed with clarity and maintainability as
first-class requirements.

----------------------------------------------------------------

CORE ARCHITECTURE

The system is built around a strict Brain / Spine separation.

BRAIN (SBC)
- Linux-class single-board computer
- High-level orchestration and tooling
- Human interface (SSH, diagnostics, logging)
- Build, deployment, and future planning logic
- No direct hardware authority

SPINE (MCU)
- Real-time microcontroller
- Deterministic execution
- Safety enforcement and motion authority
- Hardware abstraction and module control
- Final authority over actuation

This separation is non-negotiable and enforced throughout the project.

----------------------------------------------------------------

CURRENT PROJECT STATE

- Stage: Stage 2 — Infrastructure Hardening
- Motion: Not implemented; system is SAFE-by-default
- Power: Stable under load
- Spine firmware: Builds, flashes, and boots reliably
- Brain ↔ Spine protocol:
  - Normative contract adopted (v0.2)
  - Spine-side protocol ingestion stack implemented and frozen
  - CRC-verified packet parsing, validation, and stream framing complete
- Transport: Physical transport wiring (USB / CAN) pending
- Primary focus:
  Wiring transport into the validated protocol stack and enforcing behavior
  through the Spine state machine

No autonomy, motion control, or feature expansion is permitted until
Stage 2 infrastructure milestones are complete.

----------------------------------------------------------------

SAFETY AND PHILOSOPHY

- This project is not safety-certified
- Autonomy is explicitly gated and experimental
- Silence equals stop
- Setpoints never imply permission
- Safety logic lives locally on the Spine
- Clean interfaces and boring code are preferred over cleverness

If a decision matters, it must be written down.

----------------------------------------------------------------

DOCUMENTATION AND AUTHORITY

All authoritative truth lives in the project documentation under:

docs/

Key canonical documents include:

- 00_PROJECT_CONSTITUTION.md
- 01_CONTEXT_PACK.md
- 02_DECISION_LOG.md
- 04_SPECS_AND_INTERFACES.md
- BRAIN_SPINE_MESSAGE_CONTRACT.md

Chats, experiments, and tooling output are non-authoritative unless
explicitly promoted into these documents.

----------------------------------------------------------------

WHAT THIS REPOSITORY IS NOT

- Not a commercial product
- Not compliance- or safety-certified
- Not optimized for cost or mass production
- Not autonomous by default
- Not driven by feature accumulation

Learning, correctness, and clarity take precedence over speed.

----------------------------------------------------------------

END OF README
