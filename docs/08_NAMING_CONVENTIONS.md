NAMING CONVENTIONS — SCOUT32 / S2T ROVER

Status: Canonical
Authority: Project Constitution
Applies to: All code, configuration, logs, identifiers, and documentation
Last Updated: 2026-01-XX

Purpose:
This document defines mandatory naming conventions for the S2T (Scout to Titan)
project.

Naming is treated as a correctness concern, not a cosmetic one.
Names encode identity, responsibility, and authority.
Incorrect naming leads to incorrect reasoning.

Boring names are a feature, not a failure.

If an implementation changes but the role does not,
the name MUST NOT change.


----------------------------------------------------------------
1. GLOBAL RULES (BINDING)
----------------------------------------------------------------

These rules apply everywhere unless explicitly overridden.

Allowed characters:
- lowercase letters a–z
- digits 0–9
- hyphen for physical or identity names
- underscore for code identifiers and units
- dot for hierarchical telemetry names

Spaces are forbidden.
CamelCase is forbidden for identifiers.


----------------------------------------------------------------
2. CASE AND STYLE RULES
----------------------------------------------------------------

Physical module IDs:
- lowercase with hyphens

Filenames and directories:
- snake_case

Functions and variables:
- snake_case

Types and classes:
- PascalCase

Constants and enums:
- SCREAMING_SNAKE_CASE

Telemetry fields:
- lowercase, dot-separated, with unit suffixes


----------------------------------------------------------------
3. IDENTITY VS IMPLEMENTATION
----------------------------------------------------------------

Names MUST describe what a thing is, not how it is built.

Names MUST NOT encode:
- chip models
- vendors
- protocols
- algorithms
- electrical details

Those belong in specifications, not names.

If the role is unchanged, the name is unchanged.
If the role changes materially, it is a new identity.


----------------------------------------------------------------
4. MODULE AND BOARD NAMING
----------------------------------------------------------------

A module is any replaceable, self-owned physical or logical unit.

Module ID format:
<domain>-<role>-<index>

Where:
- domain is a high-level functional area
- role is the specific responsibility
- index is a two-digit decimal number (00–99)

Indices are stable and never reused for a different role.


Standard domains include:
- pwr   (power)
- ctl   (control / compute)
- sns   (sensors)
- com   (communication)
- ui    (user interface)
- dbg   (debug / safety)
- mech  (mechanical)

New domains may be added deliberately.


Example module IDs:
- ctl-spine-00
- pwr-dist-00
- pwr-bms-00
- sns-imu-00
- sns-enc-02
- ui-oled-00
- dbg-vitals-00
- com-can-00


----------------------------------------------------------------
5. MECHANICAL SUBASSEMBLIES
----------------------------------------------------------------

Mechanical assemblies follow the same scheme:

- mech-chassis-00
- mech-wheel-fl-00
- mech-susp-fr-00

Location suffixes such as fl, fr, rl, rr are permitted where meaningful.


----------------------------------------------------------------
6. SENSOR NAMING
----------------------------------------------------------------

Sensors have two distinct identities:
1. the physical device
2. the measurements it produces

These are intentionally separate.


Sensor device IDs:
- sns-imu-00
- sns-tof-01
- sns-temp-00

Indices are assigned by mounting position, not purchase order.


Telemetry field naming:
<source>.<quantity>_<unit>

Implicit units are forbidden.


Telemetry examples:
- sns-imu-00.accel_mps2
- sns-imu-00.gyro_rps
- sns-imu-00.temp_c
- sns-enc-02.omega_rps
- sns-tof-01.range_m
- pwr-bms-00.pack_v
- pwr-bms-00.current_a


Common unit suffixes:
- _m
- _mm
- _s
- _ms
- _us
- _v
- _a
- _w
- _c
- _rps
- _mps
- _mps2


----------------------------------------------------------------
7. AXES AND MOTION NAMING
----------------------------------------------------------------

An axis is an abstract controllable degree of freedom exposed by the Spine.

Axis naming format:
axis.<function>_<side>

Examples:
- axis.drive_left
- axis.drive_right
- axis.steer_front
- axis.arm_joint_02

Numeric axis IDs remain protocol authority.
Names are descriptive only.


Axis telemetry and commands:
- axis.drive_left.cmd_mps
- axis.drive_left.meas_mps
- axis.drive_right.fault


----------------------------------------------------------------
8. FIRMWARE ARTIFACT NAMING
----------------------------------------------------------------

Firmware artifacts must be traceable and sortable.

Preferred filename format:
<module>_fw_v<major>.<minor>.<patch>_<yyyymmdd>_<gitshort>.uf2

Examples:
- ctl-spine-00_fw_v0.1.0_20260101_a1b2c3d.uf2
- dbg-vitals-00_fw_v0.1.0_20260101_a1b2c3d.uf2

Short form is allowed where necessary:
<module>_v<major>.<minor>.<patch>_<gitshort>.uf2


----------------------------------------------------------------
9. REPOSITORY AND FILE NAMING
----------------------------------------------------------------

Directory names:
- snake_case
- plural for collections

Recommended top-level layout:
- docs
- brain
- spine
- firmware
- modules


Module directories use module IDs with underscores:
- modules/ctl_spine_00
- modules/sns_imu_00


----------------------------------------------------------------
10. CODE IDENTIFIER CONVENTIONS
----------------------------------------------------------------

Files:
- snake_case.c
- snake_case.cpp
- snake_case.py
- snake_case.h

Types and classes:
- PascalCase

Functions and variables:
- snake_case

Constants and enums:
- SCREAMING_SNAKE_CASE


----------------------------------------------------------------
11. HARDWARE PIN NAMING
----------------------------------------------------------------

Pins are identity-relevant and must be named.

Pin naming format:
PIN_<DOMAIN>_<SIGNAL>

Examples:
- PIN_I2C_SDA
- PIN_I2C_SCL
- PIN_CAN_RX
- PIN_CAN_TX
- PIN_MOTOR_EN

Raw GPIO numbers must not appear outside low-level HAL code.


----------------------------------------------------------------
12. LOGGING AND HUMAN-FACING OUTPUT
----------------------------------------------------------------

Logs must use canonical names.
Prefer telemetry-style naming where possible.

Example:
sns-imu-00.gyro_rps=1.24
axis.drive_left.meas_mps=0.31


----------------------------------------------------------------
13. CHANGE POLICY
----------------------------------------------------------------

Changes to this document are breaking.

Any change requires:
- an update to this file
- an entry in the Decision Log

Extensions are allowed.
Renaming existing identities is strongly discouraged.


----------------------------------------------------------------
14. PROGRESSIVE IDENTITY POLICY
----------------------------------------------------------------

Module IDs are immutable.

Once assigned, a module ID MUST NOT be:
- reused
- reassigned
- renamed in place

If a role changes sufficiently to require renaming,
a new module ID MUST be allocated.

Indices are monotonic.
Gaps are allowed.
Retired indices are never reused.

Historical continuity is preserved by retirement, not overwrite.


----------------------------------------------------------------
15. MODULE REGISTRY REQUIREMENT
----------------------------------------------------------------

A registry of module IDs MUST be maintained.

At minimum it records:
- module ID
- status
- date assigned
- notes
- superseded-by relationship (if any)

Example entries may appear for illustration only.
Real entries must be explicitly promoted.


----------------------------------------------------------------
APPENDIX A — NARRATIVE VS TECHNICAL TERMINOLOGY
----------------------------------------------------------------

Status: Canonical
Enforcement: Strict
Authority: Project Constitution
Context: S2T (Scout to Titan)

Purpose:
This appendix prevents semantic drift and refactoring debt by strictly
separating narrative identity from technical architecture.

Narrative terms describe the project journey.
Technical terms describe system behavior.


A1. CORE DISTINCTION

Narrative Identity:
What the robot or platform represents in the project timeline.

Technical Architecture:
What a component does, what authority it has, and how it behaves.

Narrative terms exist for humans.
Technical terms exist for code.

Code functions.
Code does not tell stories.


A2. NARRATIVE TERMS

Narrative terms include:
- S2T
- Scout
- Titan

Narrative terms are permitted only in:
- documentation
- configuration
- platform selection
- non-behavioral metadata

Narrative terms MUST NOT define logic, authority, or interfaces.


A3. TECHNICAL TERMS

Technical terms include:
- Brain
- Spine
- Motion
- Safety
- Transport
- Protocol

Technical terms MUST be used in code identifiers, logic, logs,
and error messages.


A4. ABSOLUTE PROHIBITION

Narrative terms MUST NEVER be used to define system logic.

Logic tied to narrative names will eventually become incorrect.


A5. IDENTIFIER RULES

Forbidden identifier patterns:
- ScoutMotor
- TitanController
- S2TPlanner

Required patterns:
- brain_<role>
- spine_<role>
- motion_<function>
- safety_<function>


A6. CONDITIONAL LOGIC RULES

Logic MUST NOT branch on narrative identity.

Logic MUST branch on capabilities, flags, or declared features.


A7. FILE AND PATH RULES

Narrative terms MAY appear only in configuration paths.

They are forbidden in source paths.


A8. LOGGING RULES

Logs MUST use technical terminology.

They must describe system behavior, not narrative state.


A9. VIOLATION HANDLING

Violations of this appendix are correctness errors.
They MUST be corrected before acceptance.

No exceptions.


END OF NAMING CONVENTIONS
