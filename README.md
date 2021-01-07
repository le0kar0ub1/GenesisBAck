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

## Run

release mode: run the given rom normaly

>   ./target/release/GenesisBack-$version.bin <path_to_tom>

debug mode: run the given rom in a gdb-like debugger

>   ./target/debug/GenesisBack-$version.bin <path_to_tom>

## About

The project is divided into 4 fat parts.

`Module` | `Description`                                  | `Link`                                 
---------|------------------------------------------------|----------------------------------------
 Modules | Module management                              | [src/modules](src/modules/README.md)   
 Core    | The processor soul & functionalities           | [src/core](src/core/README.md)         
 Debug   | The gdb-like debugger                          | [src/debug](src/debug/README.md)       
 MMU     | I/O memory interaction                         | [src/mmu](src/mmu/README.md)           
 GBA     | All the components which are not the processor | [src/gba](src/gba/README.md)           

## Epilogue

Feel free to fork, use, improve.
