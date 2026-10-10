# Gill

> An experimental operating-system project focused on small components, understandable code, and deliberate system design.

Gill is an ongoing systems-software project exploring how an operating system and its supporting tools can be built with a clear structure, minimal unnecessary overhead, and room for independent experimentation. The project includes work on the Gill system itself, its core utilities, and related system variants.

Gill is under active development. Names, designs, and release labels described as planned below should not be read as proof that the corresponding features are already implemented.

## Contents

- [Overview](#overview)
- [Project philosophy](#project-philosophy)
- [Project status](#project-status)
- [Project family](#project-family)
- [Architecture direction](#architecture-direction)
- [Gill Core Utilities](#gill-core-utilities)
- [Tool naming](#tool-naming)
- [Languages and development tools](#languages-and-development-tools)
- [Repository layout](#repository-layout)
- [Building and testing](#building-and-testing)
- [Development workflow](#development-workflow)
- [Design principles](#design-principles)
- [Security and reliability](#security-and-reliability)
- [Compatibility](#compatibility)
- [Licensing](#licensing)
- [Roadmap](#roadmap)
- [Contributing](#contributing)
- [Reporting issues](#reporting-issues)
- [Acknowledgements](#acknowledgements)

---

## Overview

Gill is a systems project built around experimentation with operating-system design and small, purposeful utilities. Rather than assuming that every component must be large or feature-heavy, Gill aims to make each component's role clear and to avoid work that the system does not need.

The project is being developed incrementally. Some ideas are implemented, some are prototypes, and some remain plans. This README separates design direction from confirmed implementation so that contributors can understand the project's intent without mistaking future goals for completed functionality.

### Main areas of work

- **Gill system:** the core operating-system and kernel-related project.
- **GCU — Gill Core Utilities:** a collection of small command-line utilities intended for the Gill ecosystem.
- **Gillux:** a Linux-based member of the broader Gill project family.
- **Gill9:** a Plan 9-related direction within the project family.
- **Gill dos:** a FreeDOS-related direction within the project family.

These names describe the project's areas and intended ecosystem. Their implementation status may differ; consult the relevant subdirectory and release notes for what is currently usable.

## Project philosophy

Gill's design direction emphasizes a few principles.

### Use what is needed

A component should use resources in proportion to the work it performs. Avoid adding dependencies, background services, or large frameworks when a simpler and reliable solution is sufficient.

### Prefer understandable code

Code should be readable and practical to modify. A small implementation is useful only when it remains understandable, maintainable, and safe.

### Keep components purposeful

Each utility or system component should have a clear responsibility. Avoid unnecessary layers and avoid making a simple task depend on a chain of unrelated applications.

### Keep choices deliberate

Adopt existing code or tools when they are suitable, secure, and reasonably easy to maintain. Reusing good code is a valid engineering choice; rewriting everything is not a requirement.

### Avoid unnecessary data collection

Privacy is a design concern. Components should not collect or transmit information without a clear need, user understanding, and appropriate safeguards.

### Be honest about limitations

Experimental software should clearly state what works, what is incomplete, and what has not been tested. Gill does not promise production readiness merely because a component builds or boots.

## Project status

Gill is an experimental project. Its features and components are at different stages of development.

The early Gill release naming scheme has included:

`v0.alpha.0.nt.nfs`

The suffixes are intended to communicate that tools and a file system are still needed. Release labels can change as the project develops; check the actual release notes before relying on a specific capability.

### Stability guidance

- **Experimental:** behavior and interfaces may change.
- **Alpha:** early development; incomplete features and breaking changes are expected.
- **Beta:** intended to indicate a more complete feature set, but still under testing.
- **Stable:** should be used only after the project defines and meets its stability criteria.

Do not use Gill as the only copy of important data or as a production system unless the specific version has been independently assessed for that purpose.

## Project family

Gill is intended to be the center of a family of related systems and tools.

### Gill

The core project, focused on operating-system and low-level systems experimentation.

### Gillux

Gillux is the Linux-based member of the family. Work associated with Gillux has included lightweight system utilities, boot and initialization ideas, and an ecosystem that can be adapted to the system's needs.

Planned components discussed for Gillux include:

- **OpenCinit:** a proposed initialization system.
- **GCU:** Gill Core Utilities.
- **GLASP(M)AS:** a proposed package manager and source/binary management tool.
- **ZeroScreen / ZS12:** a planned display-system direction.

These are project plans and names, not claims that all components are ready for use.

### Gill9

Gill9 is the Plan 9-related direction in the Gill family. Its concrete scope and implementation should be documented in its own source tree as they mature.

### Gill dos

Gill dos is the FreeDOS-related direction in the project family. Its current scope should be checked against the actual implementation and documentation.

---

## Architecture direction

Gill explores low-level system design. The exact architecture, interfaces, and boot process are subject to change while the project is experimental.

Architecture documentation should identify which parts are implemented and which are proposals. In particular, do not infer kernel properties, isolation guarantees, security certifications, or compatibility from project names alone.

### Kernel and system boundaries

The project has explored a small-kernel direction associated with SeL4-related work. Any concrete claim about kernel lineage, formal verification, security guarantees, or code reuse must be supported by the relevant source code and upstream licensing information.

The broader Gillux direction has also discussed a small kernel named **tinykern**, an operation and system-management layer called **okasm**, and a boundary component called **tinyProtector**. These are architectural concepts under development and should not be treated as complete or secure until the code and tests demonstrate that status.

### Boot and startup

Boot behavior is highly platform-specific. Document the supported hardware, bootloader, firmware mode, image format, and tested startup procedure for each usable build. Avoid assuming that a design that boots in an emulator will also boot on physical hardware.

### File system and utilities

A system needs a reliable way to access files and provide basic user-facing operations. File-system support and core utilities are therefore important parts of the project's development. Their availability should be stated per release rather than inferred from the roadmap.

---

## Gill Core Utilities

**GCU** means **Gill Core Utilities**. It is a collection of command-line tools developed for the Gill ecosystem, with a focus on small, direct utilities and a consistent project identity.

GCU is intended to provide familiar basic operations using Gill's own command names and implementation choices. It is not automatically a drop-in replacement for GNU Coreutils, BusyBox, or another utility suite.

### Goals

- Keep individual tools focused on one task.
- Make source code available for review and modification.
- Keep dependencies and runtime overhead deliberate.
- Provide build instructions and tests.
- Document command behavior and limitations.
- Integrate with the target system's filesystem layout.

### Current development notes

GCU has been worked on as a C++ project using C++20 and Clang/Clang++. The source file extensions, build configuration, and compiler commands in a given checkout should be treated as authoritative. If a branch contains `.c` files or a C compiler configuration, do not describe that branch as C++ without first converting and testing it.

A GCU archive or release may include command sources, build files, scripts, tests, documentation, and optional shell integrations. Check the contents of the specific version before assuming that every planned component is included.

### Example command names

The project has explored command names such as:

| Command | Intended role |
|---|---|
| `see` | List directory contents |
| `mdir` | Create a directory |
| `punch` | Create a file or update its timestamp, depending on implementation |
| `cop` | Copy files |
| `rom` | Remove files |
| `wai` | Print the current working directory |
| `type` | Print text or arguments |
| `pmad` | Change directory through shell integration |

This table describes intended roles. Exact options, edge cases, exit codes, recursive behavior, and compatibility must be checked against each command's implementation and help output.

### Shell integration and working directory

Some operations must be implemented inside the user's current shell. For example, a separate child process generally cannot change the working directory of its parent shell. A command such as `pmad` therefore needs a shell function or equivalent integration if it is intended to change the current interactive directory.

Shell integration files should be installed separately from executable programs. The final install locations depend on the target distribution and packaging policy. For a staged Gillux root filesystem, paths should be relative to that root filesystem rather than accidentally written into the host system.

### Compatibility expectations

GCU should document the behavior it actually supports. A command sharing a familiar name or purpose does not guarantee GNU-compatible flags, output formatting, symbolic-link handling, permission behavior, or exit statuses.

---

## Languages and development tools

Gill and its related projects may use different languages where appropriate. Each subproject should document its actual language and toolchain rather than assuming that the entire project uses one language.

For GCU work, the current stated direction has included:

- **C++20** for command implementations.
- **Clang/Clang++** as the compiler toolchain.
- **CMake** where used for project configuration and builds.
- Shell scripts for build orchestration or integration where appropriate.

The actual repository files determine the required tools. Check build scripts and project manifests before installing dependencies.

### Development expectations

- Keep compiler requirements documented.
- Prefer reproducible builds.
- Avoid unnecessary dependencies.
- Keep compiler warnings visible and fix meaningful warnings.
- Test error paths as well as successful paths.
- Do not claim performance superiority without reproducible measurements.

---

## Repository layout

The repository layout can change as Gill grows. A possible high-level organization is:

```text
Gill/
├── README.md
├── LICENSE
├── GCU/
│   ├── README.md
│   ├── src/
│   ├── tests/
│   └── build files
├── Gillux/
│   └── project-specific files
└── docs/
    ├── architecture.md
    ├── roadmap.md
    └── development.md
```

This is an illustrative structure, not a claim that every directory exists in the current repository. Follow the real repository tree when navigating or contributing.

### Root filesystem layout

For a Gillux filesystem image, conventional directories may include `bin`, `sbin`, `lib`, `lib64`, `etc`, `usr`, `home`, `root`, `proc`, `sys`, and `var`, depending on the design and stage of development.

Executable utilities normally belong in a directory included in the system's `PATH`, commonly `/bin` or `/usr/bin`. Shared libraries must be installed where the dynamic loader can find them. Shell integration, documentation, configuration, and source files should not be mixed indiscriminately with executables.

The correct layout must match the target system's boot process, linker configuration, and filesystem policy.

---

## Building and testing

Build instructions must be specific to the subproject and revision being used. Because Gill contains multiple areas of work, there is no single build command that necessarily builds every component.

### General workflow

1. Obtain the source repository or a release archive.
2. Read the subproject's README and build files.
3. Install the compiler, build system, and dependencies listed by that subproject.
4. Configure the build using the documented command.
5. Compile the target.
6. Run tests and review build output.
7. Test in a suitable emulator or disposable environment before trying experimental system images on hardware.

### GCU build

For GCU, use the build scripts and CMake configuration included in the exact version being built. If that version uses C++20 and Clang++, ensure that the build invokes `clang++` and that CMake enables the correct C++ standard.

Do not copy generic commands into the project documentation until they have been run successfully against the current source tree. Add the tested build command, required dependencies, expected output path, and test command here when they are confirmed.

### Testing experimental system builds

- Use an emulator or spare test device when possible.
- Keep backups of important files.
- Verify image checksums before flashing or booting images obtained from elsewhere.
- Record the hardware, firmware mode, bootloader, and version tested.
- Separate a successful build from a successful boot and from a stable system.

---

## Development workflow

A useful development cycle is:

1. Define a small, testable goal.
2. Inspect existing code and interfaces.
3. Implement the smallest maintainable change.
4. Build with the documented toolchain.
5. Test normal behavior and error handling.
6. Update relevant documentation.
7. Record known limitations.
8. Review the change before merging or releasing it.

### Code quality

Prefer clear control flow, explicit error handling, and meaningful names. Small code is not automatically better if it hides complexity or skips validation. Likewise, performance optimizations should be justified by the workload and tested rather than assumed.

### Documentation quality

Documentation should state:
- What the component does.
- What it does not do.
- Which platforms and dependencies are required.
- How to build and test it.
- Which interfaces may change.
- Which security and compatibility limitations are known.

---

## Design principles

Gill's design work can be evaluated using these questions:

- Does this component solve a real problem?
- Is there a simpler approach with acceptable reliability?
- Are the dependencies justified?
- Is the code understandable and reasonably easy to change?
- Does the component collect or transmit data unnecessarily?
- Are failures handled clearly?
- Can the behavior be tested?
- Are the limitations documented?

The objective is not to minimize every byte at any cost. The objective is to use resources deliberately while preserving correctness, maintainability, and security.

---

## Security and reliability

Gill is experimental, and security-sensitive components require special care.

- Do not assume that a small codebase is automatically secure.
- Do not claim formal verification unless it applies to the exact code and version in question.
- Validate external input and handle malformed files and metadata safely.
- Avoid running builds or scripts from untrusted sources with elevated privileges.
- Review permissions and ownership before installing files into a system root.
- Keep backups before changing boot, partition, or filesystem configuration.
- Use least privilege wherever practical.
- Report vulnerabilities privately to the maintainers when a suitable channel exists.

Kernel code, boot code, file-system code, privilege boundaries, and package managers can cause serious failures if incorrect. Treat those components as high-risk until they have been thoroughly tested.

---

## Compatibility

Compatibility should be documented per component and release.

A utility may resemble an existing Unix command without implementing all of its options or edge cases. An operating-system image may boot on one emulator or device without supporting other hardware. A Linux-based project may inherit Linux interfaces without guaranteeing compatibility with every Linux distribution.

When reporting compatibility, include:
- The exact version or commit.
- The architecture and platform.
- The tested command or workload.
- Expected and actual behavior.
- Any known limitations.

---

## Licensing

Gill-related work has discussed **GOSL — Gill's General Open Source License**. The final license status must be determined by the actual license file included in the repository.

Before redistributing the project:
- Include the complete license text.
- Confirm that the copyright holder and year are correct.
- Review the license terms for the intended use.
- Preserve separate notices for third-party components.
- Do not claim OSI approval unless the license has actually been approved by the Open Source Initiative.

Different components may have different licenses. In particular, a Linux-based distribution or a project that incorporates upstream code must retain and comply with the licenses applicable to those components. A project-level license does not override third-party licenses.

---

## Roadmap

The roadmap is directional and should be updated as implementation changes.

### Core system
- [ ] Define and document the supported architecture.
- [ ] Record the boot path and test environment.
- [ ] Implement and verify core system functionality.
- [ ] Document file-system status and limitations.
- [ ] Establish repeatable build and test procedures.

### GCU
- [ ] Document every included command and its supported options.
- [ ] Expand automated tests.
- [ ] Verify shell integration for supported shells.
- [ ] Document install paths and packaging behavior.
- [ ] Measure performance using repeatable benchmarks before making comparative claims.

### Gillux and related projects
- [ ] Document each component's implementation status.
- [ ] Establish reproducible image creation.
- [ ] Document package-management design and trust boundaries.
- [ ] Clarify startup and display-system plans as they become implemented.
- [ ] Keep the documentation synchronized with each release.

Items should be marked complete only when the implementation and relevant tests support that status.

---

## Contributing

Contributions are welcome when they fit the project's direction and can be reviewed.

1. Read the relevant subproject documentation.
2. Check existing issues or discuss substantial changes first.
3. Make a focused change with a clear purpose.
4. Include tests or reproducible verification steps where practical.
5. Update documentation and note limitations.
6. Avoid committing generated binaries, credentials, or unrelated files.
7. Describe what was changed and how it was tested.

Be respectful during review. Technical disagreement is normal; discussions should focus on evidence, correctness, maintainability, and project goals.

## Reporting issues

A useful issue report includes:

- A concise title.
- The exact version or commit.
- The operating system, architecture, and relevant hardware.
- Steps to reproduce the issue.
- Expected behavior and actual behavior.
- Relevant logs or error messages with secrets removed.
- Whether the issue is reproducible.

For boot or kernel problems, include the emulator or device model and the relevant boot configuration when safe to share. Do not publish passwords, private keys, access tokens, or other secrets.

## Acknowledgements

Gill builds on ideas, tools, and software from the wider systems-programming community. Give appropriate credit to upstream projects, authors, maintainers, and contributors whenever their work is used.

List actual third-party projects and contributors in the relevant subproject documentation, together with any notices required by their licenses.

---

## Final note

Gill is an evolving systems project. This README describes its goals, ecosystem, and development direction while distinguishing planned ideas from verified implementation. As the source tree changes, keep this document aligned with what can actually be built, tested, and used.

**For the most accurate information, consult the documentation and release notes shipped with the exact version you are using.**
