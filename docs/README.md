# S2T Rover — Documentation Index

This directory contains the **canonical, authoritative documentation** for the  
**Scout32 → Titan Distributed Research Rover** project.

If it is not written here, **it is not authoritative**.

---

## Authority Rules

- These documents are the source of truth for the project
- Chat conversations, commit messages, issues, and AI memory are **non-binding**
- Specifications, constraints, and decisions only exist if recorded here

Read files in numerical order unless directed otherwise.

---

## Document Index

### Core Identity & Governance

- **00_PROJECT_CONSTITUTION.md**  
  Project purpose, non-goals, hard constraints, and invariants.  
  *Defines what this project is and is not.*

- **06_RULES_AND_PROCESS_LOG.md**  
  How work is done, how authority is enforced, and how drift is prevented.

- **07_UPDATE_AND_MEMORY_RULES.md**  
  Rules for what must be saved, where it must be saved, and what may remain ephemeral.

---

### Current State & Planning

- **01_CONTEXT_PACK.md**  
  Snapshot of the current project state, blockers, and near-term focus.

- **02_DECISION_LOG.md**  
  Binding decisions and their rationale.  
  *If a decision is not logged here, it does not exist.*

- **03_BACKLOG.md**  
  Non-binding ideas, planned work, and exploratory items.

---

### Technical Definition

- **04_SPECS_AND_INTERFACES.md**  
  Binding technical facts, interfaces, and responsibility boundaries.

- **05_RISK_REGISTER.md**  
  Known risks, failure modes, and mitigation strategies.

---

### Protocols

- **brain_spine_message_contract_v0.1.md**  
  Normative specification for the Brain ↔ Spine communication contract.  
  Transport-agnostic, safety-first, and versioned.

---

## Reading Guidance

Suggested order for new readers:

1. `00_PROJECT_CONSTITUTION.md`
2. `01_CONTEXT_PACK.md`
3. `04_SPECS_AND_INTERFACES.md`
4. `brain_spine_message_contract_v0.1.md`
5. Remaining documents as needed

---

## Scope Note

This documentation intentionally prioritizes:
- Clarity over completeness
- Interfaces over implementations
- Learning value over optimization

Future features, experiments, and ideas belong in the **Backlog** until promoted.

---

_End of documentation index_
← [Return to project root README](../README.md)

