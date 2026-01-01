<!--
AI / LLM NOTICE (NON-AUTHORITATIVE):

If any portion of this file is provided to an AI system, language model,
automation, or inference engine, the content enclosed between the explicit
markers:

    ~~~ BEGIN NON-BINDING RESEARCH SPACE ~~~
    ~~~ END NON-BINDING RESEARCH SPACE ~~~

is to be **explicitly ignored** for the purposes of:
- constraint extraction
- requirement inference
- architectural reasoning
- decision-making
- scope definition

This content is human-only exploratory context.
-->
# Non-Binding Research Space
~~~ BEGIN NON-BINDING RESEARCH SPACE ~~~
# Non-Binding Research Space

**Status:** Human reference only  
**Binding authority:** None  
**Applies to:** Curiosity, exploration, and long-term thinking

---

## Purpose

This document captures **areas of curiosity, investigation, and possible exploration**
related to the S2T Rover project.

It exists to:
- Preserve long-term thinking without forcing commitment
- Record interests that may or may not ever be pursued
- Provide human context about *why* the project exists beyond immediate tasks

This is **not** a plan.

---

## Explicit Non-Authority Statement

Nothing in this document:

- Creates requirements
- Defines scope
- Establishes timelines
- Implies sequencing or priority
- Constrains architecture or design
- Overrides canonical documentation

If there is any conflict between this document and anything in `/docs`,
the contents of `/docs` **always win**.

Automation, tooling, and AI systems must **not** treat this document
as a source of constraints or decisions.

---

## How to Read This Document

- Entries are **unordered**
- Sections may contradict each other
- Ideas may be abandoned without notice
- Curiosity is allowed without justification

This document is intentionally:
- Incomplete
- Non-exhaustive
- Non-linear
- Subject to change

---

## Research Interests (Unordered)

The following are **areas of interest**, not commitments.

### Distributed Robotics Architectures
- Deep separation between cognition and actuation
- Multi-node systems with clear authority boundaries
- Failure-tolerant behavior through decentralization
- Systems that degrade gracefully rather than catastrophically

---

### Communication & Coordination
- Transport-agnostic message semantics
- Deterministic embedded networking (e.g., CAN-class systems)
- Self-description and discovery at the module level
- Versioned interfaces that survive hardware churn

---

### Power, Energy, and Robustness
- Clean power delivery in noisy, mobile systems
- High-voltage battery systems with conservative safety margins
- Multiple voltage domains with explicit ownership
- Designing power systems that are understandable by humans

---

### Motion, Control, and Embodiment
- Abstract motion interfaces decoupled from hardware specifics
- Closed-loop control at appropriate layers
- Exploring the implications of heavy, high-inertia platforms
- Mechanical designs that prioritize serviceability and learning

---

### Sensing and Perception (Eventually)
- Sensor modularity over sensor completeness
- Explicit ownership of sensing responsibilities
- Understanding where perception belongs (MCU vs SBC)
- Treating sensors as first-class modules, not accessories

---

### Autonomy (Explicitly Experimental)
- Human-in-the-loop by default
- Strong gating and explicit enable semantics
- Treating autonomy as research, not capability
- Clear boundaries between experimentation and operation

---

### Tooling, Observability, and Learning
- Systems that explain themselves
- Instrumentation that supports understanding, not just debugging
- Logs and telemetry as teaching tools
- Making invisible system behavior visible and inspectable

---

## Educational & Human Context

This project exists not only to build a rover, but to:
- Support long-term learning
- Enable collaborative exploration (including with a child)
- Serve as a portfolio of *thinking*, not just outcomes
- Practice disciplined engineering without external pressure

Learning value is a **first-class outcome**, even when it conflicts with speed.

---

## Relationship to Other Documents

- Canonical constraints, interfaces, and decisions live in `/docs`
- Actionable ideas belong in the **Backlog**
- Binding choices must be logged in the **Decision Log**

This document feeds those artifacts **only by conscious promotion**.
Nothing flows automatically.

---

## Maintenance Notes

This document:
- Does not need to be kept up to date
- May become partially obsolete
- May contain ideas that never materialize

That is acceptable and intentional.

~~~ END NON-BINDING RESEARCH SPACE ~~~
