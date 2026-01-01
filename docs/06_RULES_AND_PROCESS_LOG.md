# Rules & Process Log v0.1

**Project:** Scout32 Distributed Research Rover  
**Status:** Canonical  
**Last Updated:** 2025-01-XX  
**Applies To:** All chats, models, tools, and contributors (human or AI)

---

## 1. Purpose of This Log

This document defines **how work is done**, **how information is trusted**, and **how drift is prevented**.

It exists to:
- Preserve long-term coherence
- Prevent silent reinterpretation of goals
- Ensure learning, clarity, and architectural integrity
- Allow multiple AI systems to contribute without corrupting state

> If a rule here conflicts with convenience, **the rule wins**.

---

## 2. Authority Model (Non-Negotiable)

- Files are authoritative
- Chats are ephemeral
- Nothing is real unless written

Specifically:
- Canonical truth lives in project documents
- Conversations do not create decisions
- Memory inside any AI model is irrelevant and untrusted

---

## 3. Canonical Documents & Their Roles

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

## 4. Model Roles (Explicit Separation)

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

## 5. Memory Rules (Critical)

- No AI model is trusted to remember anything
- Long-term memory exists **only** in documents
- If something matters later, it must be written now
- Forgetting by a model is not a failure mode
- Memory loss is assumed; architecture compensates

---

## 6. Update Protocol (How Information Enters Canon)

All **non-hub contributions** must end with the following structured block:

```markdown
=== AUTOSAVE UPDATE ===
Source:
Date:
Scope:

Verified facts:
- …

Analysis performed:
- …

Proposed changes:
- …

Conflicts / ambiguities:
- …

Confidence level:
- …
=======================
