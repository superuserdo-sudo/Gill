# Gill

**Gill — Gill Is Light A Lot**

Gill is a lightweight, neutral, and independent operating-system project built around the **seL4 microkernel**.

Gill is not intended to be another Unix-like operating system or a reproduction of traditional Unix philosophy. Instead, Gill aims to develop its own architecture, terminology, utilities, interfaces, and design principles around a minimal microkernel foundation.

> **Keep the system light, minimal, understandable, modular, and independent.**

## Topics

- **Low-level**
- **Operating System**
- **Microkernel**
- **seL4**
- **Systems Programming**
- **C++**
- **C**
- **GCU**
- **Minimalism**
- **Modular**
- **Lightweight**
- **Independent**
- **Experimental**

## Philosophy

Gill is based on the idea that an operating system does not need to become unnecessarily large or complex to be useful.

The project focuses on building a small foundation and developing functionality as separate, focused components.

Gill values:

- Lightweight design
- Minimal code
- Modularity
- Simplicity
- Independence
- Clear interfaces
- Maintainability
- Practical functionality

Gill does not add functionality simply because another operating system has it.

A component should have a clear purpose and should remain as simple as reasonably possible while still being functional and maintainable.

## Gill / SeL4

Gill is built around the **seL4 microkernel**.

The Gill/SeL4 direction focuses on keeping the fundamental system small while allowing additional functionality to exist as separate system components.

```text
Gill / SeL4
├── Core System
├── GCU
├── System Components
├── Libraries
└── Filesystem
```

The goal is not to create a large kernel containing every possible feature.

Instead, Gill aims to provide a small foundation from which the rest of the operating system can develop.

## GCU

**GCU** stands for **Gill Core Utilities**.

GCU is part of Gill/SeL4 and provides fundamental utilities for the Gill environment.

GCU follows the same philosophy as Gill:

- Small programs
- Focused functionality
- Minimal unnecessary code
- Simple interfaces
- Independent implementations

GCU is not simply a collection of renamed Unix commands.

Its utilities are independently developed programs intended for the Gill environment.

Examples include:

```text
see
mdir
punch
cop
rom
wai
type
wami
wimarch
wimh
mos
wimt
idme
grps
mmsleep
tmo
wit
```

## Gill Terminology

Gill has its own terminology and naming conventions.

Examples:

```text
see      → directory listing
mdir     → create directory
punch    → create/update a file
cop      → copy
rom      → remove
wai      → show the current working directory
```

Gill also uses descriptive naming patterns such as:

```text
wimarch  → What Is My Architecture?
wimh     → What Is My Hostname?
wami     → Who Am I?
wit      → What Is Today?
```

These names are part of the Gill identity and are intended to make the Gill environment its own system rather than a renamed Unix environment.

## Minimalism

Minimalism is one of the central principles of Gill.

Gill attempts to avoid:

- Unnecessary code
- Unnecessary dependencies
- Unnecessary layers
- Unnecessary functionality
- Complexity without a clear purpose

Minimal does not mean intentionally incomplete.

The goal is to implement the functionality that is actually needed while keeping the implementation as small and understandable as reasonably possible.

## Modularity

Gill is designed to be modular.

The operating system can be developed component by component instead of requiring every part to be completed at the same time.

Individual components should be able to evolve independently while communicating through clear interfaces.

This allows Gill to grow without turning the entire system into one large and tightly coupled codebase.

## Independence

Gill is an independent operating-system project.

It may use existing technologies, standards, algorithms, and ideas where appropriate, but it is not intended to reproduce another operating system under a different name.

Gill develops its own:

- Terminology
- Utilities
- Interfaces
- System conventions
- Architecture
- Development philosophy

## Programming

Gill does not require every component to use one programming language.

C++ is currently an important language for Gill utilities and userland programs.

C and other languages may be used when they are more appropriate for low-level or system-specific components.

The goal is not to enforce one language everywhere, but to keep each component simple, efficient, and maintainable.

## Gill Is Not Unix

Gill is not intended to be another Unix.

Unix has had an enormous influence on computing, but Gill does not treat traditional Unix conventions as requirements.

Gill is free to use different terminology, interfaces, utilities, and architectural decisions.

The question behind a Gill component is not:

> "How did Unix do this?"

but:

> "What is the simplest and most appropriate way to do this in Gill?"

Existing ideas can still be useful.

Gill simply does not consider historical conventions mandatory.

## Neutrality

Gill is intended to be a neutral operating-system foundation.

It is not designed around a particular commercial ecosystem or traditional operating-system philosophy.

Gill can establish its own design decisions according to the actual purpose of each component.

Neutrality does not mean that Gill has no philosophy.

It means that Gill is free to develop its own philosophy instead of inheriting one by default.

## Lightweight by Design

The name **Gill — Gill Is Light A Lot** represents one of the project's central ideas.

Gill aims to remain lightweight not only in resource usage, but also in architectural complexity.

```text
Less unnecessary code.
Less unnecessary complexity.
Less unnecessary software.

More control.
More clarity.
More modularity.
```

The objective is not to make everything small at any cost.

The objective is to make the system **only as complex as it needs to be**.

## Current Development

The current version of Gill is:

```text
Gill v0.alpha.0.nt.nfs
```

This version intentionally communicates that Gill is still at a very early stage.

### Version Breakdown

```text
v0       → pre-version-1 development
alpha    → experimental development stage
0        → initial release number
nt       → Needs Tools
nfs      → Needs File System
```

Therefore:

```text
Gill v0.alpha.0.nt.nfs
```

means that Gill is currently an early experimental system that still needs important tools and a filesystem.

Gill is not presented as a finished operating system.

The version number is intended to communicate the actual development state of the project.

## Release System

Gill uses a release format based around development stages.

General formats:

```text
Gill vX.alpha.X
Gill vX.beta.X
Gill vX.stable.X
```

### Alpha

Alpha releases represent experimental development.

They may contain:

- Incomplete components
- Changing interfaces
- Experimental architecture
- Missing functionality
- Unfinished system components

### Beta

Beta releases represent a more developed stage.

The fundamental architecture should be more established, while components may still require testing, refinement, or changes.

### Stable

Stable releases represent a release considered stable for its intended scope.

Stable does not mean that Gill is permanently finished.

Future releases can still introduce new features, improvements, or architectural changes.

The `stable` label describes the stability of that particular release.

## Development Suffixes

Gill can use additional suffixes to communicate important development requirements.

Current suffixes include:

```text
nt  = Needs Tools
nfs = Needs File System
```

For example:

```text
Gill v0.alpha.0.nt.nfs
```

immediately communicates that Gill is in an early alpha state and still needs tools and a filesystem.

## Development Direction

Gill is being developed incrementally.

The current development focuses on establishing the foundations required for the system.

Current areas include:

- Gill/SeL4 core development
- GCU development
- System utilities
- System components
- Libraries
- Filesystem development
- Basic system interfaces

The project does not attempt to hide incomplete areas.

Instead, Gill's versioning system is designed to communicate the current state directly.

## Current Status

```text
Project:          Gill
Meaning:          Gill Is Light A Lot
Foundation:       seL4
Current Version:  Gill v0.alpha.0.nt.nfs
Stage:             Alpha
Status:            Experimental / Incomplete
GCU:               In development
Tools:             Needed
Filesystem:        Needed
License:           GOSL v1.0
OSI Approval:      Not approved
```

## Licensing

Gill uses **GOSL — Gill's General Open Source License**.

GOSL is intended to be a permissive license allowing broad use, modification, combination, and distribution of software, including use in open-source and closed-source projects.

**GOSL is currently not approved by the Open Source Initiative (OSI).**

GOSL is currently a project-defined license and must not be described as OSI-approved.

Any future OSI review or approval will be separate from the current development status of Gill.

## Long-Term Goal

Gill aims to grow from a small microkernel-based foundation into a complete operating-system environment while preserving its original principles.

The project intends to remain:

- Lightweight
- Modular
- Understandable
- Independent
- Practical
- Minimal where possible

Gill starts small by design.

The goal is not to build everything immediately.

The goal is to build the foundation, develop each component independently, and allow the system to grow without losing its original philosophy.

---

**Gill Is Light A Lot.**
