# GenesisBAck

A cross-plateform GBA emulator.

## Dependencies

  * `make` (dev under v4.3)
  * `curl`
  * `tar`

## Install

GenesisBAck use his own cross-compiler with frozen version, build it by executing the following command-line.
The dependencies are also checked-up.

>   ./mktoolchain/mktoolchain [$architecture]

Defaulting to the host architecture if unset.

## Build

Build all

>   make [cfg={debug|release}]

Build a part of the project, the main must be contained in the given driectory.

>   make build tgt=directory [cfg={debug|release}]

directory is given without `src` prefix. 

defaulting to `debug` if unset.

Example:

>   make build tgt=emulator/core

## Run

>   make run

## ROADMAP

- [ ] Cross-compilation
- [ ] Project Architecture
- [ ] GBA emulation
  - [ ] Processor emulation
    - [ ] ...
  - [ ] ARMV7 ISA
    - [ ] Thumb IS
    - [ ] ARMV7 IS
- [ ] GBA BIOS

## Epilogue

Feel free to fork, use, improve.
