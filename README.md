# S2T Rover (Scout → Titan)

This repository contains the **S2T Rover** project: a distributed research
rover effort focused on learning, architectural correctness, and long-term
experimentation.

**S2T (Scout to Titan)** is the project identity and development arc.
It represents the deliberate progression from early *Scout* iterations
toward the final *Titan* rover architecture.

Early physical builds may use a Scout-derived chassis for convenience,
but the project itself is not tied to any specific chassis, platform,
or mechanical implementation.

This is a **learning and research platform**, not a product.

----------------------------------------------------------------

## Why This Project Exists

The S2T Rover project exists to answer a simple question:

How do you design a robotic system that is safe, understandable,
and evolvable over time?

Rather than optimizing for features or rapid results, the project
optimizes for:

- Clear boundaries between responsibilities
- Explicit authority and safety ownership
- Systems that humans can reason about
- Designs that remain teachable years later

The rover is both a research platform and a long-term learning tool,
intended to grow in capability without losing architectural integrity.

----------------------------------------------------------------

## System Architecture Philosophy

At the core of S2T is a strict **Brain / Spine** separation.

This split exists to prevent ambiguity, hidden coupling, and unsafe
shortcuts as the system grows.

### Brain (SBC)

The Brain is a Linux-class single-board computer responsible for
non-real-time concerns:

- High-level orchestration and coordination
- Tooling, logging, deployment, and diagnostics
- Human interface and development workflow
- Generating intent and requests

The Brain has **no direct hardware or actuation authority**.
It may request actions, but it cannot permit them.

### Spine (MCU)

The Spine consists of one or more microcontrollers responsible for
real-time and safety-critical concerns:

- Deterministic execution
- Ingesting and validating Brain requests via a strict protocol
- Enforcing safety invariants locally
- Owning all real-time interfaces to hardware
- Holding final authority over whether actuation is permitted

The Spine does not plan or make mission-level decisions.
It executes validated requests only within explicitly permitted
safety bounds and defaults to SAFE behavior on silence, fault,
or ambiguity.

This separation ensures that loss of the Brain cannot result
in unsafe behavior.

----------------------------------------------------------------

## Safety and Design Principles

Safety is treated as a structural property, not a best-effort feature.

Core principles include:

- This project is **not safety-certified**
- Autonomy is **explicitly gated and experimental**
- Motion and actuation are disabled by default
- Silence equals stop
- Setpoints never imply permission
- Safety logic lives locally on the Spine
- Ambiguity always fails SAFE

Code quality is treated as a safety concern.
Boring, readable, and explicit code is preferred over cleverness.

If a decision matters, **it must be written down**.

----------------------------------------------------------------

## Learning and Evolution

S2T is designed to evolve over time without requiring rewrites.

Key ideas include:

- Interfaces are more important than implementations
- Hardware choices are replaceable
- Mechanical designs may change without forcing software redesign
- Early experiments are allowed, but must be clearly labeled
- Long-term clarity outweighs short-term convenience

The project is intentionally structured so that future contributors
(including future versions of the author and their child) can
understand not just what the system does, but why it was built
that way.

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
- Not tied to a specific chassis or mechanical platform
- Not autonomous by default
- Not driven by feature accumulation

Learning, correctness, and clarity take precedence over speed.

----------------------------------------------------------------

End of README
