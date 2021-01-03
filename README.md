# GenesisBAck

A cross-plateform GBA emulator.

## Dependencies

  * `make` (dev under v4.3)
  * `curl`
  * `tar`

## Install

GenesisBAck use his own cross-compiler with frozen version, build it by executing the following command-line. -> currently unusable, using host compiler.

Install the dependencies.

>   ./mktoolchain/mktoolchain [$architecture]

Defaulting to the host architecture if unset.

## Build

>   make [cfg={debug|release}]

defaulting to `debug` if unset.

## Configure

The file `inc/cfg.h` have some preprocessors configuration.

`DEBUG_STATE_MASTER`:
  * Debug mode: Dissassemble each executed instruction
  * Release mode: nothing

`VERBOSE_RUN`:
  * Debug mode: nothing
  * Release mode: Log for each cpu cycle

## Run

release mode: run the given rom normaly

>   ./target/release/GenesisBack-$version.bin <path_to_tom>

debug mode: run the given rom in a gdb-like debugger

>   ./target/release/GenesisBack-$version.bin <path_to_tom>

## About

The project is divided into 4 fat modules.

| `Core`                               | `Debug`                  | `MMU`                   | `SoC`                                          |
|--------------------------------------|--------------------------|-------------------------|------------------------------------------------|
| The processor soul & functionalities | The gdb-like debugger    |  I/O memory interaction | All the components which are not the processor |

## Epilogue

Feel free to fork, use, improve.
