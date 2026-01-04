CODING STANDARDS — SCOUT32 / S2T ROVER

Status: Canonical
Authority: Project Constitution
Applies to: All Brain, Spine, and Module code
Intent: Enforce Linux-kernel-level code quality, safety, and reviewability

This document defines how code MUST be written in this project.
If code violates this document, it is incorrect, regardless of functionality.


1. PRIME DIRECTIVE

Clarity, correctness, and safety override all other concerns.

Boring code is preferred.
Explicit code is preferred.
Reviewable code is mandatory.

Cleverness is treated as a liability.


2. ARCHITECTURAL BOUNDARY RULES (NON-NEGOTIABLE)

These rules are absolute.

The Brain MUST NOT directly drive hardware.
The Spine is the final authority over motion and actuation.
Loss of Brain communication MUST result in a safe, non-moving state.
Safety logic MUST live on the Spine and be locally enforceable.

Any change that blurs Brain/Spine responsibility is rejected.


3. LEXICON DEPENDENCY (MANDATORY)

All contributors MUST use terminology exactly as defined in lexicon.md.

If a term is used inconsistently with the lexicon, the code is incorrect.


4. MANDATORY SAFETY INVARIANTS

Every change is reviewed against these invariants:

1. Spine is the final motion authority.
2. Silence equals stop.
3. Setpoints NEVER imply permission.
4. Motion requires explicit enable.
5. Malformed or unknown messages MUST NOT enable motion.
6. Safety behavior must be deterministic.
7. Units are explicit everywhere.
8. No unbounded loops in Spine.
9. Modules have no implicit trust.
10. Failure modes MUST be safe by default.

Violating or weakening any invariant is grounds for rejection.


5. NAMING CONVENTIONS (BINDING)

Naming rules are law and come from 08_NAMING_CONVENTIONS.md.

Additional rules:
Names encode meaning, not implementation.
If you cannot name it precisely, you do not understand it.
Names define reviewability.


5.1 BANNED VAGUENESS (HARD RULE)

The following identifiers are DISALLOWED unless explicitly justified:

manager
handler
util
helper
misc
stuff
thing
data
process
do_*

These obscure ownership and responsibility.


6. REVIEW REJECTION RULES

6.1 HARD REJECTS (PATCH IS REFUSED)

Refactor and behavior change in the same commit.
Implicit units or scaling.
Unnamed constants in safety or protocol paths.
Unbounded loops in Spine.
Runtime dynamic memory allocation in Spine.
Implicit struct packing for wire formats.
Code that can enable motion on malformed input.
“Shouldn’t happen” logic in safety paths.

6.2 SOFT REJECTS (REQUIRE STRONG JUSTIFICATION)

New abstraction layers.
Indirection added for hypothetical future use.
Macros or templates replacing clear code.
Utility or helper dumping grounds.
Concurrency without explicit ownership model.


7. COMPLEXITY BUDGETS

Complexity must be bounded to prevent entropy.

7.1 SPINE (MCU)

No recursion.
No exceptions.
No RTTI.
No runtime dynamic allocation.
All loops MUST be bounded.
Functions SHOULD NOT exceed approximately 50 lines without justification.
Cyclomatic complexity SHOULD remain low and obvious.
All periodic work MUST declare a time budget.

Write C++ as “C with namespaces.”

7.2 BRAIN (LINUX)

Dynamic allocation allowed.
Concurrency allowed, but ownership model must be explicit.
Task lifecycles must be documented.
Background tasks must be stoppable and observable.


8. CRITICAL PATH CODING PATTERN

Safety- and motion-critical code MUST follow explicit early-return structure.

Required order:

Validate session.
Validate motion enable.
Validate timing or keepalive.
Apply command.

Nested logic, clever branching, or implicit fallthrough is prohibited on critical paths.


9. PROTOCOL SERIALIZATION DOCTRINE (BINDING)

Wire formats are part of the API.

Transport provides bytes only; semantics live in protocol.
Endianness MUST be specified and documented.
Structs MUST NOT be serialized directly unless:
Packing is explicit.
Size is validated with static_assert.
Alignment assumptions are documented.
All protocol structs MUST include a version field.
Integrity checks MUST be validated before use.
Malformed packets MUST be safely ignored or faulted.


10. UNITS AND CONSTANTS

All physical quantities MUST declare units explicitly.
Magic numbers are prohibited.
Timing, scaling, and safety constants MUST be named, centralized, and commented.
Contract-frozen constants MUST NOT change without a protocol version bump.


11. OWNERSHIP AND LIFETIME RULES

Every resource has a single, obvious owner.
Ownership transfer MUST be explicit.
Shared ownership is prohibited in Spine.
Lifetimes must be documented for cross-boundary data.

If ownership is unclear, the code is rejected.


12. ERROR HANDLING AND SAFETY BEHAVIOR

Errors are handled explicitly and locally.
Unknown message types MUST NOT trigger action.
Safety faults MUST be reflected in state or heartbeat telemetry.
“Best effort” safety logic is prohibited.

Determinism is required.


13. COMMIT DISCIPLINE (MANDATORY)

Each commit MUST:
Change one thing.
Preserve all invariants.
Be reviewable in isolation.

Required commit message format:

Subject:
<subsystem>: <imperative summary>

Body:
Problem:
Approach:
Safety:
Tests:

Commits that mix refactor and behavior are rejected.


14. TESTING EXPECTATIONS (STAGE 2 MINIMUM)

At minimum, protocol and safety work must test:

Framing resynchronization.
Header integrity failure.
Payload integrity failure.
Keepalive timeout behavior.
Setpoint-before-enable handling.
Unknown message handling.
Safe behavior on silence.

Tests may be crude.
Absence of tests is unacceptable.


15. DOCUMENTATION UPDATE DISCIPLINE

If a change affects:

Interfaces or semantics, update Specs or Contract.
Binding decisions, update Decision Log.
Operational truth, update Context Pack.
Risk profile, update Risk Register.

If it is not written, it is not real.


16. REVIEW RUBRIC (SELF-CHECK)

If a reviewer can reasonably ask any of the following,
the change is not ready:

Who owns this?
What authority does it have?
What happens on failure?
What are the units?
What invariant prevents unsafe behavior?
How does it recover from corruption or silence?
Why does this abstraction exist?


END OF CODING STANDARDS
