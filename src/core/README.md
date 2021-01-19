# Core module

This module is the more or less the ARM7TDMI soul and the RELEASE routine scheduler (the DEBUG routine being the debug module).

The emulation respects the processor pipeling with the *fetch*, *decode* (called *route* here ), and *exec* but not simultaneously.

The core contain also the panic function which can be used by every fonction to stop the program if a fatal error is encountered.

Cycle  | Job
-------|----------
 Fetch | Using MMU module, read 2 or 4 bytes at the address in the program counter register (used during next cycle)
 Route | Return the function which will execute the instruction (route the prefetch)
 Exec  | Finaly execute the instruction and modify the system (exec the prefetch)

 