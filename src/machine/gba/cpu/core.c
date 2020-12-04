/******************************************************************************
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include  "machine/gba/cpu/core.h"

/**
 * The totality of the ar7dmi registers
 */
struct arm7tdmi arm7tdmi;

/**
 * Current operation mode
 */
uint32_t operation_mode = (uint32_t)PROCESSOR_OPERATION_MODE_UNDEFINED;

/**
 * Current state
 */
uint32_t state = (uint32_t)PROCESSOR_STATE_ARM;

/**
 * AR7TDMI user operation mode and ARM state
 * The registers below target the good one in the arm7tdmi mass
 */
static struct arm7tdmi_arm_opmode arm_usr = {
    .r0   = &arm7tdmi.r0,
    .r1   = &arm7tdmi.r1,
    .r2   = &arm7tdmi.r2,
    .r3   = &arm7tdmi.r3,
    .r4   = &arm7tdmi.r4,
    .r5   = &arm7tdmi.r5,
    .r6   = &arm7tdmi.r6,
    .r7   = &arm7tdmi.r7,
    .r8   = &arm7tdmi.r8,
    .r9   = &arm7tdmi.r9,
    .r10  = &arm7tdmi.r10,
    .r11  = &arm7tdmi.r11,
    .r12  = &arm7tdmi.r12,
    .r13  = &arm7tdmi.r13,
    .r14  = &arm7tdmi.r14,
    .r15  = &arm7tdmi.r15,
    .cpsr = &arm7tdmi.cpsr,
    .spsr = NULL
};

/**
 * AR7TDMI fiq operation mode and ARM state
 * The registers below target the good one in the arm7tdmi mass
 */
static struct arm7tdmi_arm_opmode arm_fiq = {
    .r0   = &arm7tdmi.r0,
    .r1   = &arm7tdmi.r1,
    .r2   = &arm7tdmi.r2,
    .r3   = &arm7tdmi.r3,
    .r4   = &arm7tdmi.r4,
    .r5   = &arm7tdmi.r5,
    .r6   = &arm7tdmi.r6,
    .r7   = &arm7tdmi.r7,
    .r8   = &arm7tdmi.r8_fiq,
    .r9   = &arm7tdmi.r9_fiq,
    .r10  = &arm7tdmi.r10_fiq,
    .r11  = &arm7tdmi.r11_fiq,
    .r12  = &arm7tdmi.r12_fiq,
    .r13  = &arm7tdmi.r13_fiq,
    .r14  = &arm7tdmi.r14_fiq,
    .r15  = &arm7tdmi.r15,
    .cpsr = &arm7tdmi.cpsr,
    .spsr = &arm7tdmi.spsr_fiq
};

/**
 * AR7TDMI irq operation mode and ARM state
 * The registers below target the good one in the arm7tdmi mass
 */
static struct arm7tdmi_arm_opmode arm_irq = {
    .r0   = &arm7tdmi.r0,
    .r1   = &arm7tdmi.r1,
    .r2   = &arm7tdmi.r2,
    .r3   = &arm7tdmi.r3,
    .r4   = &arm7tdmi.r4,
    .r5   = &arm7tdmi.r5,
    .r6   = &arm7tdmi.r6,
    .r7   = &arm7tdmi.r7,
    .r8   = &arm7tdmi.r8,
    .r9   = &arm7tdmi.r9,
    .r10  = &arm7tdmi.r10,
    .r11  = &arm7tdmi.r11,
    .r12  = &arm7tdmi.r12,
    .r13  = &arm7tdmi.r13_irq,
    .r14  = &arm7tdmi.r14_irq,
    .r15  = &arm7tdmi.r15,
    .cpsr = &arm7tdmi.cpsr,
    .spsr = &arm7tdmi.spsr_irq
};

/**
 * AR7TDMI supervisor operation mode and ARM state
 * The registers below target the good one in the arm7tdmi mass
 */
static struct arm7tdmi_arm_opmode arm_svc = {
    .r0   = &arm7tdmi.r0,
    .r1   = &arm7tdmi.r1,
    .r2   = &arm7tdmi.r2,
    .r3   = &arm7tdmi.r3,
    .r4   = &arm7tdmi.r4,
    .r5   = &arm7tdmi.r5,
    .r6   = &arm7tdmi.r6,
    .r7   = &arm7tdmi.r7,
    .r8   = &arm7tdmi.r8,
    .r9   = &arm7tdmi.r9,
    .r10  = &arm7tdmi.r10,
    .r11  = &arm7tdmi.r11,
    .r12  = &arm7tdmi.r12,
    .r13  = &arm7tdmi.r13_svc,
    .r14  = &arm7tdmi.r14_svc,
    .r15  = &arm7tdmi.r15,
    .cpsr = &arm7tdmi.cpsr,
    .spsr = &arm7tdmi.spsr_svc
};

/**
 * AR7TDMI abort operation mode and ARM state
 * The registers below target the good one in the arm7tdmi mass
 */
static struct arm7tdmi_arm_opmode arm_abt = {
    .r0   = &arm7tdmi.r0,
    .r1   = &arm7tdmi.r1,
    .r2   = &arm7tdmi.r2,
    .r3   = &arm7tdmi.r3,
    .r4   = &arm7tdmi.r4,
    .r5   = &arm7tdmi.r5,
    .r6   = &arm7tdmi.r6,
    .r7   = &arm7tdmi.r7,
    .r8   = &arm7tdmi.r8,
    .r9   = &arm7tdmi.r9,
    .r10  = &arm7tdmi.r10,
    .r11  = &arm7tdmi.r11,
    .r12  = &arm7tdmi.r12,
    .r13  = &arm7tdmi.r13_abt,
    .r14  = &arm7tdmi.r14_abt,
    .r15  = &arm7tdmi.r15,
    .cpsr = &arm7tdmi.cpsr,
    .spsr = &arm7tdmi.spsr_abt
};

/**
 * AR7TDMI system operation mode and ARM state
 * The registers below target the good one in the arm7tdmi mass
 */
static struct arm7tdmi_arm_opmode arm_sys = {
    .r0   = &arm7tdmi.r0,
    .r1   = &arm7tdmi.r1,
    .r2   = &arm7tdmi.r2,
    .r3   = &arm7tdmi.r3,
    .r4   = &arm7tdmi.r4,
    .r5   = &arm7tdmi.r5,
    .r6   = &arm7tdmi.r6,
    .r7   = &arm7tdmi.r7,
    .r8   = &arm7tdmi.r8,
    .r9   = &arm7tdmi.r9,
    .r10  = &arm7tdmi.r10,
    .r11  = &arm7tdmi.r11,
    .r12  = &arm7tdmi.r12,
    .r13  = &arm7tdmi.r13,
    .r14  = &arm7tdmi.r14,
    .r15  = &arm7tdmi.r15,
    .cpsr = &arm7tdmi.cpsr,
    .spsr = NULL
};

/**
 * AR7TDMI undefined operation mode and ARM state
 * The registers below target the good one in the arm7tdmi mass
 */
static struct arm7tdmi_arm_opmode arm_und = {
    .r0   = &arm7tdmi.r0,
    .r1   = &arm7tdmi.r1,
    .r2   = &arm7tdmi.r2,
    .r3   = &arm7tdmi.r3,
    .r4   = &arm7tdmi.r4,
    .r5   = &arm7tdmi.r5,
    .r6   = &arm7tdmi.r6,
    .r7   = &arm7tdmi.r7,
    .r8   = &arm7tdmi.r8,
    .r9   = &arm7tdmi.r9,
    .r10  = &arm7tdmi.r10,
    .r11  = &arm7tdmi.r11,
    .r12  = &arm7tdmi.r12,
    .r13  = &arm7tdmi.r13_und,
    .r14  = &arm7tdmi.r14_und,
    .r15  = &arm7tdmi.r15,
    .cpsr = &arm7tdmi.cpsr,
    .spsr = &arm7tdmi.spsr_und
};

/**
 * AR7TDMI user operation mode and Thumb state
 * The registers below target the good one in the arm7tdmi mass
 */
static struct arm7tdmi_thumb_opmode thumb_usr = {
    .r0   = &arm7tdmi.r0,
    .r1   = &arm7tdmi.r1,
    .r2   = &arm7tdmi.r2,
    .r3   = &arm7tdmi.r3,
    .r4   = &arm7tdmi.r4,
    .r5   = &arm7tdmi.r5,
    .r6   = &arm7tdmi.r6,
    .r7   = &arm7tdmi.r7,
    .r13  = &arm7tdmi.r13,
    .r14  = &arm7tdmi.r14,
    .r15  = &arm7tdmi.r15,
    .cpsr = &arm7tdmi.cpsr,
    .spsr = NULL
};

/**
 * AR7TDMI fiq operation mode and Thumb state
 * The registers below target the good one in the arm7tdmi mass
 */
static struct arm7tdmi_thumb_opmode thumb_fiq = {
    .r0   = &arm7tdmi.r0,
    .r1   = &arm7tdmi.r1,
    .r2   = &arm7tdmi.r2,
    .r3   = &arm7tdmi.r3,
    .r4   = &arm7tdmi.r4,
    .r5   = &arm7tdmi.r5,
    .r6   = &arm7tdmi.r6,
    .r7   = &arm7tdmi.r7,
    .r13  = &arm7tdmi.r13_fiq,
    .r14  = &arm7tdmi.r14_fiq,
    .r15  = &arm7tdmi.r15,
    .cpsr = &arm7tdmi.cpsr,
    .spsr = &arm7tdmi.spsr_fiq
};

/**
 * AR7TDMI irq operation mode and Thumb state
 * The registers below target the good one in the arm7tdmi mass
 */
static struct arm7tdmi_thumb_opmode thumb_irq = {
    .r0   = &arm7tdmi.r0,
    .r1   = &arm7tdmi.r1,
    .r2   = &arm7tdmi.r2,
    .r3   = &arm7tdmi.r3,
    .r4   = &arm7tdmi.r4,
    .r5   = &arm7tdmi.r5,
    .r6   = &arm7tdmi.r6,
    .r7   = &arm7tdmi.r7,
    .r13  = &arm7tdmi.r13_irq,
    .r14  = &arm7tdmi.r14_irq,
    .r15  = &arm7tdmi.r15,
    .cpsr = &arm7tdmi.cpsr,
    .spsr = &arm7tdmi.spsr_irq
};

/**
 * AR7TDMI supervisor operation mode and Thumb state
 * The registers below target the good one in the arm7tdmi mass
 */
static struct arm7tdmi_thumb_opmode thumb_svc = {
    .r0   = &arm7tdmi.r0,
    .r1   = &arm7tdmi.r1,
    .r2   = &arm7tdmi.r2,
    .r3   = &arm7tdmi.r3,
    .r4   = &arm7tdmi.r4,
    .r5   = &arm7tdmi.r5,
    .r6   = &arm7tdmi.r6,
    .r7   = &arm7tdmi.r7,
    .r13  = &arm7tdmi.r13_svc,
    .r14  = &arm7tdmi.r14_svc,
    .r15  = &arm7tdmi.r15,
    .cpsr = &arm7tdmi.cpsr,
    .spsr = &arm7tdmi.spsr_svc
};

/**
 * AR7TDMI abort operation mode and Thumb state
 * The registers below target the good one in the arm7tdmi mass
 */
static struct arm7tdmi_thumb_opmode thumb_abt = {
    .r0   = &arm7tdmi.r0,
    .r1   = &arm7tdmi.r1,
    .r2   = &arm7tdmi.r2,
    .r3   = &arm7tdmi.r3,
    .r4   = &arm7tdmi.r4,
    .r5   = &arm7tdmi.r5,
    .r6   = &arm7tdmi.r6,
    .r7   = &arm7tdmi.r7,
    .r13  = &arm7tdmi.r13_abt,
    .r14  = &arm7tdmi.r14_abt,
    .r15  = &arm7tdmi.r15,
    .cpsr = &arm7tdmi.cpsr,
    .spsr = &arm7tdmi.spsr_abt
};

/**
 * AR7TDMI system operation mode and Thumb state
 * The registers below target the good one in the arm7tdmi mass
 */
static struct arm7tdmi_thumb_opmode thumb_sys = {
    .r0   = &arm7tdmi.r0,
    .r1   = &arm7tdmi.r1,
    .r2   = &arm7tdmi.r2,
    .r3   = &arm7tdmi.r3,
    .r4   = &arm7tdmi.r4,
    .r5   = &arm7tdmi.r5,
    .r6   = &arm7tdmi.r6,
    .r7   = &arm7tdmi.r7,
    .r13  = &arm7tdmi.r13,
    .r14  = &arm7tdmi.r14,
    .r15  = &arm7tdmi.r15,
    .cpsr = &arm7tdmi.cpsr,
    .spsr = NULL
};

/**
 * AR7TDMI undefined operation mode and Thumb state
 * The registers below target the good one in the arm7tdmi mass
 */
static struct arm7tdmi_thumb_opmode thumb_und = {
    .r0   = &arm7tdmi.r0,
    .r1   = &arm7tdmi.r1,
    .r2   = &arm7tdmi.r2,
    .r3   = &arm7tdmi.r3,
    .r4   = &arm7tdmi.r4,
    .r5   = &arm7tdmi.r5,
    .r6   = &arm7tdmi.r6,
    .r7   = &arm7tdmi.r7,
    .r13  = &arm7tdmi.r13_und,
    .r14  = &arm7tdmi.r14_und,
    .r15  = &arm7tdmi.r15,
    .cpsr = &arm7tdmi.cpsr,
    .spsr = &arm7tdmi.spsr_und
};


/*
static void *get_operation_mode_handler(void)
{
    switch (operation_mode)
    {
        case PROCESSOR_OPERATION_MODE_USER:
            return (state == PROCESSOR_STATE_ARM ? &arm_usr : &thumb_usr);
        case PROCESSOR_OPERATION_MODE_FIQ:
            return (state == PROCESSOR_STATE_ARM ? &arm_fiq : &thumb_fiq);
        case PROCESSOR_OPERATION_MODE_IRQ:
            return (state == PROCESSOR_STATE_ARM ? &arm_irq : &thumb_irq);
        case PROCESSOR_OPERATION_MODE_SUPERVISOR:
            return (state == PROCESSOR_STATE_ARM ? &arm_svc : &thumb_svc);
        case PROCESSOR_OPERATION_MODE_ABORT:
            return (state == PROCESSOR_STATE_ARM ? &arm_abt : &thumb_abt);
        case PROCESSOR_OPERATION_MODE_SYSTEM:
            return (state == PROCESSOR_STATE_ARM ? &arm_sys : &thumb_sys);
        case PROCESSOR_OPERATION_MODE_UNDEFINED:
            return (state == PROCESSOR_STATE_ARM ? &arm_und : &thumb_und);
        default:
            panic("[ARM7TDMI]: invalid operation mode");
    }
}
*/