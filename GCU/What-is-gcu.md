GCU — Gill Core Utilities

GCU stands for Gill Core Utilities.

GCU is the collection of fundamental user-facing utilities that provides the basic command-line functionality of the Gill environment.

Instead of depending on traditional Unix utility conventions, GCU provides utilities designed specifically for Gill, with their own names, interfaces, behavior, and conventions.

GCU is not simply a renamed collection of Unix commands. Each utility is intended to be an independent, focused component of the Gill environment.

Examples include:

see      → view the contents of a directory
mdir     → create a directory
punch    → create or update a file
cop      → copy files or other supported objects
rom      → remove files or other supported objects
wai      → show the current working location
wami     → identify the current user
wimarch  → show the system architecture
wimh     → show the system hostname
wit      → show the current date/time information

The purpose of GCU is to provide the user with the essential tools needed to interact with Gill while keeping each utility small, understandable, modular, and independent.

GCU is part of the Gill/SeL4 system environment and is intended to grow alongside the rest of Gill as additional system functionality is implemented.

GCU Philosophy

GCU follows the same principles as Gill:

- Small utilities
- Focused responsibilities
- Minimal unnecessary code
- Clear interfaces
- Independent components
- Gill-specific terminology
- No requirement to reproduce traditional Unix conventions

The goal is not to avoid useful ideas from existing systems. The goal is to design utilities according to what Gill actually needs.
