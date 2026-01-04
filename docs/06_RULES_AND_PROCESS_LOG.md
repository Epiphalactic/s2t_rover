# Rules & Process Log v0.1

> **PROCESS CLARIFICATION**
>
> This document defines **how work is conducted and reconciled**, not what the system is.
> Process rules exist to prevent drift, ambiguity, and unsafe shortcuts.
>
> This document does NOT override:
> - The Project Constitution (identity-level rules)
> - The Context Pack (current state)
> - Specifications & Interfaces (technical truth)
>
> If a process rule conflicts with canonical documents, the canonical documents prevail.




**Project:** Scout32 Distributed Research Rover  
**Status:** Process-Canonical (Non-Authoritative)
**Last Updated:** 2025-01-XX  
**Applies To:** All chats, models, tools, and contributors (human or AI)

---

## 01. Purpose of This Log

This document defines **how work is done**, **how information is trusted**, and **how drift is prevented**.

It exists to:
- Preserve long-term coherence
- Prevent silent reinterpretation of goals
- Ensure learning, clarity, and architectural integrity
- Allow multiple AI systems to contribute without corrupting state

> If a rule here conflicts with convenience, **the rule wins**.

---

## 02. Authority Model (Non-Negotiable)

- Files are authoritative
- Chats are ephemeral
- Nothing is real unless written

Specifically:
- Canonical truth lives in project documents
- Conversations do not create decisions
- Memory inside any AI model is irrelevant and untrusted

---

## 03. Canonical Documents & Their Roles

| File                         | Purpose                                      |
|------------------------------|----------------------------------------------|
| `00_PROJECT_CONSTITUTION.md` | Identity, purpose, constraints, invariants   |
| `01_CONTEXT_PACK.md`         | Current state and immediate focus             |
| `02_DECISION_LOG.md`         | Binding decisions and rationale               |
| `03_BACKLOG.md`              | Ideas, work items, ambition buffer            |
| `04_SPECS_AND_INTERFACES.md` | Facts, interfaces, limits                    |
| `05_RISK_REGISTER.md`        | Known risks and mitigations                  |
| `06_RULES_AND_PROCESS_LOG.md`| How the system evolves                       |

> No other document may override these.

---

## 04. Model Roles (Explicit Separation)

### 4.1 ChatGPT Project (Hub)

Responsibilities:
- Maintain canonical documents
- Merge updates
- Check for invariant violations
- Reject or flag conflicts
- Never improvise architecture without instruction

---

### 4.2 External Models (Spokes: Gemini, Grok, etc.)

Characteristics:
- Stateless reasoning engines

They may receive **only**:
- Context Pack excerpts
- Relevant specs
- One clearly scoped task

They must:
- Return structured output
- Own no memory
- Hold no authority

---

### 4.3 Creative / Sandbox Chats

Purpose:
- Generate ideas only

Rules:
- Output must be harvested and vetted
- No direct write access to canon

---

## 05. Memory Rules (Critical)

- No AI model is trusted to remember anything
- Long-term memory exists **only** in documents
- If something matters later, it must be written now
- Forgetting by a model is not a failure mode
- Memory loss is assumed; architecture compensates

---

## 06. Update Protocol (How Information Enters Canon)

### Required Update Block (for non-hub contributions)

All non-hub contributions must include:

- Source
- Date
- Scope
- Verified facts
- Analysis performed
- Proposed changes
- Conflicts / ambiguities
- Confidence level


## 07. Canonical Reconciliation Rule

When discrepancies are discovered between:
- project documentation
- code
- observed system behavior
- or human memory

The following reconciliation order SHALL be used:

1. **Observed system behavior**
2. **Current code and build artifacts**
3. **Context Pack (authoritative snapshot)**
4. **Decision Log (historical rationale)**
5. **Project History (narrative record)**
6. **Chats and external notes**

Corrections MUST be made explicitly and traceably.
Silent fixes or retroactive rewrites are forbidden.


## 08. Session Close-Out Checklist (Recommended)

At the end of a work session, answer the following:

- Did observed behavior differ from documented state?
- Did the Context Pack need updating?
- Did any backlog item change status?
- Was a binding decision made?
- Was any assumption corrected?

If the answer to any is “yes”, perform reconciliation before starting new work.

##  09. Project History Handling

The project maintains a single chronological history document:

- `PROJECT_HISTORY.md`

This document is **non-canonical** and exists to preserve narrative context,
learning, and rationale.

Rules:
- No other document shall duplicate historical timelines or event summaries
- Canonical documents may reference the Project History but must not derive authority from it
- In case of discrepancy, canonical documents prevail over Project History
