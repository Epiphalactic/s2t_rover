# 09_MODULE_RULES.md
# Module Rules (Canonical)

This document defines the **binding rules** for any attachable module participating in the Scout32 / S2T Rover system.

These rules apply **only to modules** and **do not redefine project-level authority**, which is established in the Project Constitution (`00_PROJECT_CONSTITUTION.md`).  
Any module that violates these rules is not a valid system participant.

---

## 1. Scope and Purpose

The purpose of these rules is to:

- Enable safe, modular attachment and removal of subsystems
- Prevent accidental or malicious actuation
- Preserve zero-trust assumptions
- Allow system evolution without rewrites

Modules are assumed to be:
- replaceable
- optional
- fallible

Safety and authority are enforced structurally, not by module goodwill.

---

## 2. Module Lifecycle States (Required)

Every module SHALL exist in exactly one of the following states:

### 2.1 DETECTED
- Physical presence confirmed
- LV_STANDBY power only
- Communication permitted
- No actuation possible

### 2.2 QUARANTINED
- Module identity known or unknown
- Trust not yet established or invalidated
- Awaiting verification and/or user approval
- HV_ACTUATION disabled

### 2.3 ENROLLED
- Module identity bound to system
- Capabilities reviewed and authorized
- Continuity established
- Still non-actuating until enabled

### 2.4 OPERATIONAL
- Trust established
- HV_ACTUATION explicitly enabled
- Module may generate actuation signals **within authorized capabilities only**

### 2.5 REVOKED / FAULTED
- Trust withdrawn or fault detected
- HV_ACTUATION removed immediately
- Requires re-approval to proceed

State transitions SHALL be explicit and auditable.

---

## 3. Identity and Trust

### 3.1 Module UID
- Each module SHALL have a stable unique identifier (Module UID)
- The UID is used for registry binding and continuity checks
- UID alone SHALL NOT grant authority

### 3.2 Pairing Secret
- Each module SHALL be provisioned with a shared secret at build time
- The secret SHALL NOT be transmitted in the clear
- Authentication SHALL be performed via challenge–response

---

## 4. Initialization and Handshake

### 4.1 Required Handshake Elements
On attachment or reinitialization, a module SHALL provide:
- Module UID
- Continuity token (`session_ctr`)
- Capability descriptor (or hash)
- Proof of pairing secret knowledge

### 4.2 Authorization Rules
- Unknown modules SHALL enter QUARANTINED state
- Known modules with mismatched continuity or capabilities SHALL enter QUARANTINED state
- Promotion beyond QUARANTINED requires explicit authorization

---

## 5. Continuity and Anti-Cloning Mechanism

### 5.1 Continuity Counter (`session_ctr`)
- A monotonic counter stored on both the module and the system registry
- Represents successful trusted initialization sessions

### 5.2 Increment Rules
- `session_ctr` SHALL increment **only** after a successful initialization handshake and commit
- It SHALL NOT increment on raw power cycles, brownouts, or transient resets

### 5.3 Two-Phase Commit
- The system proposes the next counter value
- The module stores and acknowledges
- The system commits and acknowledges
- Only then may the module enter OPERATIONAL state

### 5.4 Mismatch Handling
- Any mismatch SHALL force QUARANTINED state
- Mismatch resolution requires explicit user approval
- Upon approval, both sides SHALL be resynchronized

This mechanism is a **tamper and continuity signal**, not a permanent lockout.

---

## 6. Service and Bootloader Events

- Entering bootloader or service mode SHALL invalidate `session_ctr`
- Invalidated continuity SHALL force QUARANTINED state on next attach
- Re-approval is required before operation may resume

Service actions are treated as intentional trust-breaking events.

---

## 7. Capability Declaration and Authorization

### 7.1 Declaration
- Modules MAY declare capabilities during initialization
- Declarations are advisory only

### 7.2 Authorization
- The system SHALL explicitly authorize a subset of declared capabilities
- Authorized capabilities SHALL be stored in the registry
- Modules SHALL NOT self-grant new capabilities

### 7.3 Changes
- Capability changes require re-approval
- Unauthorized capability use SHALL result in immediate revocation

---

## 8. Power Architecture (Dual-Rail Requirement)

### 8.1 Required Power Domains
Each module port SHALL provide:
- **LV_STANDBY**: low-power rail for MCU and communications
- **HV_ACTUATION**: switched rail for actuators and energy delivery

### 8.2 Default States
- HV_ACTUATION SHALL be OFF by default
- LV_STANDBY MAY remain ON for discovery and diagnostics

### 8.3 Internal Module Design
Modules SHALL be designed such that:
- MCU and communications operate fully from LV_STANDBY
- No actuation is possible from LV_STANDBY alone
- Actuators require HV_ACTUATION and authorization

---

## 9. Enable Gating (Strongly Recommended)

- Module ports SHOULD include a logic-level ENABLE signal
- Actuation SHOULD require both HV_ACTUATION and ENABLE asserted
- ENABLE SHALL be removable immediately for fast shutdown

---

## 10. Failure Semantics

- Missing modules are valid system states
- Silence, ambiguity, or fault SHALL fail SAFE
- Loss of trust, heartbeat, or authorization SHALL immediately disable HV_ACTUATION

---

## 11. Human-in-the-Loop Requirement

- First-time module enrollment requires explicit human approval
- Continuity or capability mismatches require explicit human approval
- Approval MUST be local (physical presence)
- No remote path may approve trust or power enable

---

## 12. Non-Negotiable Principles

- Identity does not imply authority
- Authority is enforced physically (power and enable)
- Modules are replaceable; safety is not
- Default behavior is INERT
- Evolution is expected; rewrites are not

---

Any module that does not comply with these rules SHALL be considered non-participatory and SHALL NOT be permitted to actuate under any circumstances.