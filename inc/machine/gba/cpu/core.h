/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _MACHINE_GBA_ARM7TDMI_CORE_H_
# define _MACHINE_GBA_ARM7TDMI_CORE_H_

# include "genesisback.h"
# include <stdint.h>
# include "machine/gba/gba.h"
# include "machine/shared/cpu.h"

/**
 * The cpu has to deal with these type of data only
 */
typedef uint8_t   byte_t;
typedef uint16_t  hword_t;
typedef uint32_t  word_t;

/**
 * Define the 2 processor states
 */
enum {
    PROCESSOR_STATE_ARM,
    PROCESSOR_STATE_THUMB
};

/**
 * Define the 7 operations modes of the processor
 */
enum {
    PROCESSOR_OPERATION_MODE_USER = 0,
    PROCESSOR_OPERATION_MODE_FIQ = 1,
    PROCESSOR_OPERATION_MODE_IRQ = 2, 
    PROCESSOR_OPERATION_MODE_SUPERVISOR = 3,
    PROCESSOR_OPERATION_MODE_ABORT = 4, 
    PROCESSOR_OPERATION_MODE_SYSTEM = 5,
    PROCESSOR_OPERATION_MODE_UNDEFINED = 6
};

/**
 * All processor registers over operation modes
 */
struct arm7tdmi
{
    /* Basics registers */
    struct register32 r0;

    struct register32 r1;

    struct register32 r2;

    struct register32 r3;

    struct register32 r4;

    struct register32 r5;

    struct register32 r6;

    struct register32 r7;

    struct register32 r8;
    struct register32 r8_fiq;

    struct register32 r9;
    struct register32 r9_fiq;

    struct register32 r10;
    struct register32 r10_fiq;

    struct register32 r11;
    struct register32 r11_fiq;

    struct register32 r12;
    struct register32 r12_fiq;

    struct register32 r13;
    struct register32 r13_fiq;
    struct register32 r13_svc;
    struct register32 r13_abt;
    struct register32 r13_irq;
    struct register32 r13_und;

    struct register32 r14;
    struct register32 r14_fiq;
    struct register32 r14_svc;
    struct register32 r14_abt;
    struct register32 r14_irq;
    struct register32 r14_und;

    struct register32 r15;

    /* Controls registers */
    struct register32 cpsr;

    struct register32 spsr_fiq;
    struct register32 spsr_svc;
    struct register32 spsr_abt;
    struct register32 spsr_irq;
    struct register32 spsr_und;
};

/**
 * Will be staticaly declared for each mode and will refered to the godd register in the arm7dmi global
 */
struct arm7tdmi_tgtmode
{
    struct register32 *r0;
    struct register32 *r1;
    struct register32 *r2;
    struct register32 *r3;
    struct register32 *r4;
    struct register32 *r5;
    struct register32 *r6;
    struct register32 *r7;
    struct register32 *r8;
    struct register32 *r9;
    struct register32 *r10;
    struct register32 *r11;
    struct register32 *r12;
    struct register32 *r13;
    struct register32 *r14;
    struct register32 *r15;

    struct register32 *cpsr;
    struct register32 *spsr;
};

#endif /* _MACHINE_GBA_ARM7TDMI_CORE_H_ */