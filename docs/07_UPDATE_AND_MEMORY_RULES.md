# Update & Memory Rules v0.1

**Project:** Scout32 Distributed Research Rover  
**Status:** Canonical  
**Last Updated:** 2025-01-XX  
**Authority:** Project Constitution v0.1  

---

## Purpose

This document defines:

- When information **must be saved**
- Where it **must be saved**
- What is allowed to remain **ephemeral**
- How short-term context crosses chats **without becoming canon**

It exists to prevent:

- Silent loss of critical knowledge
- Over-documentation
- Architecture drift caused by “helpful” assumptions

---

## 1. The Prime Rule (Memorize This)

> If forgetting it would cause **rework, confusion, or unsafe behavior**, it must be written down.  
> If forgetting it only causes **inconvenience**, it stays ephemeral.

This rule overrides all instincts to “just remember it later.”

---

## 2. Save / Don’t Save Decision Test (Mandatory)

For **any new information**, ask the following **in order**:

1. Would a future version of me be upset if this was gone?
2. Would a new chat need this to continue correctly?
3. Does this constrain future design choices?
4. Does this change how subsystems interact?
5. Does this create or resolve risk?

**Decision rule:**
- If **any answer is YES** → it must be saved
- If **all answers are NO** → it stays ephemeral

---

## 3. What MUST Be Saved (Non-Negotiable)

The following categories **must always** be written to canonical documents.

### A. Constraints & Invariants
Examples:
- Power limits
- Safety rules
- Architectural boundaries
- “Never do X” rules

**Destination:**
- `00_PROJECT_CONSTITUTION.md`
- `04_SPECS_AND_INTERFACES.md`

---

### B. Decisions
Examples:
- Tradeoff resolutions
- Selections (even “temporary” ones)
- Rejections with rationale

**Destination:**
- `02_DECISION_LOG.md`

---

### C. Interfaces
Examples:
- Message formats
- Timing expectations
- Ownership boundaries
- Assumptions between systems

**Destination:**
- `04_SPECS_AND_INTERFACES.md`

---

### D. State Transitions
Examples:
- “We now have X working”
- “This blocker is resolved”
- “This approach failed”

**Destination:**
- `01_CONTEXT_PACK.md`  
- (Optionally also `02_DECISION_LOG.md` if binding)

---

### E. Risks & Failures
Examples:
- New failure modes
- Incidents
- Near-misses

**Destination:**
- `05_RISK_REGISTER.md`

---

## 4. What Must NOT Be Saved (Equally Important)

The following must **not** enter canon:

- Brainstorming
- Half-formed ideas
- Personal preferences
- Temporary debugging thoughts
- “What if we someday…” ideas

**Destination:**
- Nowhere  
- Or `03_BACKLOG.md` as **Exploratory**

> Saving these increases noise and creates false constraints.

---

## 5. Short-Term Memory (Cross-Chat Working Context)

### 5.1 Definition

Short-term memory is context that:

- Is relevant for the next few sessions
- Has not hardened into a decision
- Would clutter canonical documents if saved permanently

**Examples:**
- Current debugging hypothesis
- Suspected root cause
- Temporary workaround
- Experimental direction under test

---

### 5.2 Where Short-Term Memory Lives

Short-term memory lives **only** in:

- `01_CONTEXT_PACK.md` (explicit section)

When needed, add:

```markdown
## Working Notes (Temporary)

- Hypothesis: power noise from XYZ regulator
- Testing approach: swap supply, re-run throttling test
- Valid until: next power test
