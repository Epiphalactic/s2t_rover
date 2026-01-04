PROJECT LEXICON — SCOUT32 / S2T ROVER

Status: Canonical
Authority: Project Constitution
Applies to: All documentation, code, reviews, and discussions

This document defines binding meanings of project-specific terms.
If a term appears here, it has a precise meaning.
If a term does not appear here, it MUST NOT be relied on as shared knowledge.
Ambiguous or overloaded use of terminology is treated as a correctness error.


1. PROJECT IDENTITY

S2T
Acronym for “Scout to Titan.”
S2T is the name of the project and represents the overall journey:
the progression from the initial Scout platform to the final Titan rover.

S2T is both:
- the project identifier
- the conceptual arc of development and iteration

All stages, platforms, and architectures exist within the S2T project.


2. SYSTEM TOPOLOGY (LOGICAL ROLES)

Brain
A Linux-class compute node responsible for orchestration, tooling, logging,
deployment, and human interaction.
The Brain has NO direct hardware authority.
The Brain may request actions but cannot permit them.

Spine
A microcontroller-class node responsible for real-time execution,
safety enforcement, and final authority over motion and actuation.
The Spine enforces safety locally and autonomously.


3. PLATFORM CODENAMES (PHYSICAL INSTANCES AND VEHICLES)

Titan (Brain Codename)
Codename for the Raspberry Pi–class Brain compute platform.
Used to refer to the physical Brain node and its software environment.

Titan (Rover Codename)
Codename for the intended final rover platform and architecture.
Represents the long-term target system of the S2T project.

Scout (Spine Codename)
Codename for the RP2040-class Spine microcontroller platform.
Used to refer to the physical Spine node and its firmware environment.

Scout (Rover Chassis Codename)
Codename for the initial physical rover chassis used for early iterations,
integration, and testing.
Scout is an implementation vehicle, not the final rover identity.

The S2T journey explicitly refers to the evolution from the Scout rover
toward the Titan rover.

Context determines whether Titan or Scout refers to:
- a compute node
- a microcontroller node
- or a physical rover chassis

When ambiguity is possible, the reference MUST be clarified explicitly.


4. AUTHORITY AND CONTROL

Authority
The right to permit an action to occur.
Authority cannot be inferred, implied, or delegated implicitly.

Request
A non-binding suggestion sent by a non-authoritative entity.
Requests may be ignored without error.

Final Authority
The entity that makes the irreversible decision.
For motion and actuation, this is ALWAYS the Spine.

Permission
An explicit grant that allows an action to be taken.
Permissions are stateful and revocable.


5. SAFETY AND MOTION SEMANTICS

Motion Enable
An explicit permission gate that allows motion-related commands to be acted upon.
Without motion enable, all motion-related commands are ignored.

Setpoint
A target value such as velocity, position, torque, or duty.
Setpoints NEVER imply permission.
Setpoints are ignored unless motion enable is active.

Silence Equals Stop
A mandatory safety invariant.
Loss of valid communication causes the Spine to enter a safe, non-moving state.

Hold Timeout
A bounded time window after which the Spine MUST revoke motion enable
if no valid keepalive is received.

Safe State
A system condition in which no motion or hazardous actuation can occur.
Safe state must be reachable deterministically and locally on the Spine.


6. BRAIN TO SPINE PROTOCOL TERMS

Transport
A byte-delivery mechanism such as USB serial or CAN.
Transport provides no semantics, ordering guarantees, or safety meaning.

Packet
The smallest contract-defined unit exchanged between Brain and Spine.
A packet consists of header, payload, and trailer.

Message
A typed payload contained within a packet.
Messages are interpreted only within the context of the active protocol version.

Session
A pairing between one Brain boot instance and one Spine boot instance.
Sessions are invalidated on reboot, reset, or explicit termination.

Heartbeat
A message whose sole purpose is to assert liveness.
Heartbeats carry no command authority.

Keepalive
A valid, protocol-defined indication of continued Brain presence.
Setpoints do NOT count as keepalive.

Fault
A detected condition that violates protocol, safety, or system assumptions.
Faults may revoke permissions or force safe state.


7. MODULE SYSTEM TERMS

Module
An attachable, optional subsystem.
Modules have no implicit trust, authority, or permission.

Detected
The module’s identity is visible, but no power or authority is granted.

Quarantined
The module is electrically present but functionally inert.

Enrolled
The module has been explicitly trusted by a human or higher-level authority.

Operational
The module is powered and allowed to act within its defined role.

Revoked
Module trust has been withdrawn.
Re-enrollment is required before any operation may resume.

LV_STANDBY
Low-voltage power rail used only for identification and minimal logic.

HV_ACTUATION
High-power rail capable of causing motion or physical effect.


8. DOCUMENTATION SEMANTICS

Canonical
Binding truth.
May only be changed via explicit decision recorded in the Decision Log.

Normative
Defines required behavior.
Implementations MUST comply.

Non-authoritative
Informational only.
May not override canonical documents.

Superseded
Replaced information retained for historical reference.
Superseded text MUST remain visible and be struck through, not deleted.

Source of Truth
The document explicitly designated as authoritative for a given topic.
Chats are never a source of truth.


9. PROJECT STAGES

Stage 1 — Bring-up
Power, flashing, basic observability, and identity verification.

Stage 2 — Infrastructure Hardening
Stable interfaces, safety invariants, deterministic liveness,
and observability.
Motion logic remains gated until Stage 2 completion.

Stage 3 and beyond
Later phases of the S2T journey.
Out of scope for this document.


10. LANGUAGE ENFORCEMENT RULES

Terms defined in this lexicon MUST be used consistently.
Synonyms are prohibited unless explicitly defined here.
Overloading terms with new meanings is prohibited.

If a reviewer must ask what a term means,
the term has been used incorrectly.


END OF PROJECT LEXICON
