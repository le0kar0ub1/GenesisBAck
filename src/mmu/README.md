# MMU module

This is the interface between the emulated GBA memory area and the emulator.

The GBA area is allocated by this module and all the memory access are made here.

There are no check on access, this module is mostly used for the address translation.