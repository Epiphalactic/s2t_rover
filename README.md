# S2T Rover (Scout32 → Titan)

This repository contains **Scout32**, a distributed research rover project
focused on learning, architectural correctness, and long-term experimentation.

The project operates under the **S2T (Scout to Titan)** identity, representing
the deliberate progression from early *Scout* platforms toward the final
*Titan* rover architecture.

This is a **learning and research platform**, not a product.

----------------------------------------------------------------

## Overview

Scout32 exists to explore and teach:

- Distributed robotic system design
- Clean separation of responsibilities
- Safety-first architecture
- Maintainable, human-readable embedded systems

The project prioritizes **clarity, correctness, and understanding**
over features, performance, or speed of development.

----------------------------------------------------------------

## System Architecture

The system is built around a strict **Brain / Spine** separation.

This separation is mandatory and enforced throughout the project.

### Brain (SBC)

A Linux-class single-board computer responsible for:

- High-level orchestration and coordination
- Tooling, logging, deployment, and diagnostics
- Human interface (SSH, development workflow)
- Generating requests and intent only

The Brain has **no direct hardware or actuation authority**.

### Spine (MCU)

One or more microcontrollers responsible for:

- Deterministic, real-time execution
- Ingesting and validating Brain requests via a strict protocol
- Enforcing safety invariants locally
- Owning all real-time interfaces to hardware
- Holding final authority over whether actuation is permitted

The Spine does **not** plan or make mission-level decisions.
It executes validated requests only within explicitly permitted safety bounds
and defaults to SAFE behavior on silence, fault, or ambiguity.

----------------------------------------------------------------

## Safety and Design Philosophy

- This project is **not safety-certified**
- Autonomy is **explicitly gated and experimental**
- Motion and actuation are disabled by default
- Silence equals stop
- Setpoints never imply permission
- Safety logic lives locally on the Spine

Clean interfaces and boring, understandable code are preferred over cleverness.

If a decision matters, **it must be written down**.

----------------------------------------------------------------

## Current Project Status

- Current stage: **Stage 2 — Infrastructure Hardening**
- Motion control: **Not implemented**
- Spine firmware: Builds, flashes, and boots reliably
- Brain ↔ Spine protocol: **Normative and adopted (v0.2)**
- Spine-side protocol ingestion stack implemented and frozen
- Transport wiring (USB / CAN): Pending integration

No motion, autonomy, or feature expansion is permitted until
Stage 2 infrastructure milestones are complete.

----------------------------------------------------------------

## Documentation and Authority

All authoritative project documentation lives in:

docs/

Key documents include:

- Project Constitution — identity, constraints, invariants
- Context Pack — current authoritative project state
- Decision Log — binding architectural decisions
- Specs and Interfaces — technical facts and interfaces
- Brain ↔ Spine Message Contract — normative protocol specification

Chats, experiments, and tooling output are **non-authoritative**
unless explicitly promoted into project documents.

----------------------------------------------------------------

## What This Project Is Not

- Not a commercial product
- Not compliance- or safety-certified
- Not optimized for cost or mass production
- Not autonomous by default
- Not driven by feature accumulation

Learning, correctness, and clarity take precedence over speed.

----------------------------------------------------------------

End of README
