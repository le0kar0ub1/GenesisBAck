# GBA module - Under heavy dev, nothing is working

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

## Architecture choice

Except for the Video and Sound module which will run more or less continuously on threads because they must update their content and do job permanently.

All of the others modules will be memory trigger:
  1. When a write is performed in a selected memory area (The I/O mmap of the GBA) a thread will be created with the write information.

  2. The thread will wait for the previous one which run `FOR THE INVOVED MODULE` (if 10 modules are using this way, a maximum of 10 threads will run at 
  a time but a lot of thread can wait for the previous to terminate, a process of non-wait based on the job will be implemented)

  3. When the previous is terminated, the new one take the control. This is FIFO implementation regardless of the module.