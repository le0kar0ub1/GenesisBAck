/******************************************************************************
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include  "core/core.h"

/**
 * The totality of the ar7tdmi registers
 */
struct arm7tdmi arm7tdmi;

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

/**
 * There are no rights consideration, the capcity to R/W must be decided before this function call.
 */
struct register32 *register_read_ptr(uint32_t id)
{
    if (id < 8)
        return (((struct register32 **)&arm7tdmi)[id]);
    if (arm7tdmi.cpsr.state == PROCESSOR_STATE_ARM && id < 16)
    {
        switch (arm7tdmi.cpsr.opmode)
        {
            case PROCESSOR_OPERATION_MODE_USER:
                return (((struct register32 **)&arm_usr)[id]);
                break;
            case PROCESSOR_OPERATION_MODE_FIQ:
                return (((struct register32 **)&arm_fiq)[id]);
                break;
            case PROCESSOR_OPERATION_MODE_IRQ:
                return (((struct register32 **)&arm_irq)[id]);
                break;
            case PROCESSOR_OPERATION_MODE_SUPERVISOR:
                return (((struct register32 **)&arm_svc)[id]);
                break;
            case PROCESSOR_OPERATION_MODE_ABORT:
                return (((struct register32 **)&arm_abt)[id]);
                break;
            case PROCESSOR_OPERATION_MODE_SYSTEM:
                return (((struct register32 **)&arm_sys)[id]);
                break;
            case PROCESSOR_OPERATION_MODE_UNDEFINED:
                return (((struct register32 **)&arm_und)[id]);
                break;
            default:
                LOG_ERR(__func__, "Invalid operation mode");
                panic("Invalid operation mode");
        }
    }
    LOG_DEBUG(__func__, "Register id: %d, state: %d, opmode: %d", id, arm7tdmi.cpsr.state, arm7tdmi.cpsr.opmode);
    panic(__func__);
}

uint8_t register_read8(uint32_t id)
{
    return ((*(register_read_ptr(id))).r8);
}

uint16_t register_read16(uint32_t id)
{
    return ((*(register_read_ptr(id))).r16);
}

uint32_t register_read32(uint32_t id)
{
    return ((*(register_read_ptr(id))).r32);
}

void register_write8(uint32_t id, uint8_t val)
{
    ((*(register_read_ptr(id))).r8) = val;
}

void register_write16(uint32_t id, uint16_t val)
{
    ((*(register_read_ptr(id))).r16) = val;
}

void register_write32(uint32_t id, uint32_t val)
{
    ((*(register_read_ptr(id))).r32) = val;
}

struct register_psr register_read_cpsr(void)
{
    return (arm7tdmi.cpsr);
}

void register_write_cpsr(uint32_t wr)
{
    arm7tdmi.cpsr.raw = wr;
}

struct register_psr register_read_spsr(void)
{
    switch (arm7tdmi.cpsr.opmode)
    {
        case PROCESSOR_OPERATION_MODE_FIQ:
            return (*arm_usr.spsr);
            break;
        case PROCESSOR_OPERATION_MODE_IRQ:
            return (*arm_irq.spsr);
            break;
        case PROCESSOR_OPERATION_MODE_SUPERVISOR:
            return (*arm_svc.spsr);
            break;
        case PROCESSOR_OPERATION_MODE_ABORT:
            return (*arm_abt.spsr);
            break;
        case PROCESSOR_OPERATION_MODE_UNDEFINED:
            return (*arm_und.spsr);
            break;
        default:
            LOG_ERR(__func__, "Invalid operation mode");
            panic("Invalid operation mode");
    }
}

void register_write_spsr(uint32_t wr)
{
    switch (arm7tdmi.cpsr.opmode)
    {
        case PROCESSOR_OPERATION_MODE_FIQ:
            (*arm_usr.spsr).raw = wr;
            break;
        case PROCESSOR_OPERATION_MODE_IRQ:
            (*arm_irq.spsr).raw = wr;
            break;
        case PROCESSOR_OPERATION_MODE_SUPERVISOR:
            (*arm_svc.spsr).raw = wr;
            break;
        case PROCESSOR_OPERATION_MODE_ABORT:
            (*arm_abt.spsr).raw = wr;
            break;
        case PROCESSOR_OPERATION_MODE_UNDEFINED:
            (*arm_und.spsr).raw = wr;
            break;
        default:
            LOG_ERR(__func__, "Invalid operation mode");
            panic("Invalid operation mode");
    }
}