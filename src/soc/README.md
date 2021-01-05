# SoC module - Under heavy dev, nothing is working

The most aboundant part which contain all the components of the GBA which are not 'essentials'. All Of them are registered as a module and a lot of them will run on threads.

All the modules are configured using register in memory, [here is the list](https://problemkaputt.de/gbatek.htm#gbaiomap).

 Module    | Threaded | Description
-----------|----------|---------------------------
DMA        | Yes      | The 4 DMA engines of the GBA
Interrupt  | ?        | The interrupt controller irq/fiq and IE, fiq are unused by the GBA
Keypad     | Nop      | The keypad, work with the interrupt controller
Serial     | Yes      | Serial communication and ports, there are two serials
Sound      | Yes      | Sound effects and music
System     | Yes      | Power control, waitstate
Timer      | Yes      | 4 timers, so basic
Video      | Yes      | The LCD screen control