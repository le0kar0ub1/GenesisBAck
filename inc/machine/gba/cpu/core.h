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
    PROCESSOR_STATE_ARM   = 0b0,
    PROCESSOR_STATE_THUMB = 0b1
};

/**
 * Define the 7 operations modes of the processor
 */
enum {
    PROCESSOR_OPERATION_MODE_USER       = 0b10000,
    PROCESSOR_OPERATION_MODE_FIQ        = 0b10001,
    PROCESSOR_OPERATION_MODE_IRQ        = 0b10010, 
    PROCESSOR_OPERATION_MODE_SUPERVISOR = 0b10011,
    PROCESSOR_OPERATION_MODE_ABORT      = 0b10111, 
    PROCESSOR_OPERATION_MODE_UNDEFINED  = 0b11011,
    PROCESSOR_OPERATION_MODE_SYSTEM     = 0b11111
};

/**
 * CPSR register articulation
 */
struct arm7tdmi_psr
{
    union
    {
        struct
        {
            uint32_t opmode          : 5;
            uint32_t state           : 1;
            uint32_t fiq_disable     : 1;
            uint32_t irq_disable     : 1;
            uint32_t _reserved       : 20;
            // uint32_t sticky_overflow : 1;
            uint32_t overflow_flg    : 1;
            uint32_t carry_flg       : 1;
            uint32_t zero_flg        : 1;
            uint32_t sign_flg        : 1;
        };
        uint32_t val;
    };
};

static_assert(sizeof(struct arm7tdmi_psr) == 4);

/**
 * Program counter AKA r15
 */
struct arm7tdmi_r15
{
    union
    {
        struct
        {
            uint32_t e;
        };
        uint32_t val;
    };
};

static_assert(sizeof(struct arm7tdmi_r15) == 4);

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
    struct arm7tdmi_psr cpsr;

    struct arm7tdmi_psr spsr_fiq;
    struct arm7tdmi_psr spsr_svc;
    struct arm7tdmi_psr spsr_abt;
    struct arm7tdmi_psr spsr_irq;
    struct arm7tdmi_psr spsr_und;
};

/**
 * Will be staticaly declared for each mode and will refered to the good register in the arm7dmi global
 */
struct arm7tdmi_arm_opmode
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
    /* stack pointer */
    struct register32 *r13;
    /* link register */
    struct register32 *r14;
    /* program counter */
    struct register32 *r15;

    struct arm7tdmi_psr *cpsr;
    struct arm7tdmi_psr *spsr;
};

/**
 * Will be staticaly declared for each mode and will refered to the good register in the arm7dmi global
 */
struct arm7tdmi_thumb_opmode
{
    struct register32 *r0;
    struct register32 *r1;
    struct register32 *r2;
    struct register32 *r3;
    struct register32 *r4;
    struct register32 *r5;
    struct register32 *r6;
    struct register32 *r7;
    /* stack pointer */
    struct register32 *r13;
    /* link register */
    struct register32 *r14;
    /* program counter */
    struct register32 *r15;

    struct arm7tdmi_psr *cpsr;
    struct arm7tdmi_psr *spsr;
};

#endif /* _MACHINE_GBA_ARM7TDMI_CORE_H_ */