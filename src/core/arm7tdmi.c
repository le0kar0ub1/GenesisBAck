/******************************************************************************
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include "core/core.h"
# include <string.h>

/**
 * All processor registers over operation modes
 */
struct arm7tdmi
{
    /* Basics registers */
    uint32_t r0;

    uint32_t r1;

    uint32_t r2;

    uint32_t r3;

    uint32_t r4;

    uint32_t r5;

    uint32_t r6;

    uint32_t r7;

    uint32_t r8;
    uint32_t r8_fiq;

    uint32_t r9;
    uint32_t r9_fiq;

    uint32_t r10;
    uint32_t r10_fiq;

    uint32_t r11;
    uint32_t r11_fiq;

    uint32_t r12;
    uint32_t r12_fiq;

    uint32_t r13;
    uint32_t r13_fiq;
    uint32_t r13_svc;
    uint32_t r13_abt;
    uint32_t r13_irq;
    uint32_t r13_und;

    uint32_t r14;
    uint32_t r14_fiq;
    uint32_t r14_svc;
    uint32_t r14_abt;
    uint32_t r14_irq;
    uint32_t r14_und;

    uint32_t r15;

    /* Controls registers */
    struct register_psr cpsr;

    struct register_psr spsr_fiq;
    struct register_psr spsr_svc;
    struct register_psr spsr_abt;
    struct register_psr spsr_irq;
    struct register_psr spsr_und;

    uint32_t prefetch;
    bool     running;
};

/**
 * The totality of the ar7tdmi registers
 */
static struct arm7tdmi arm7tdmi;

/**
 * AR7TDMI user operation mode and ARM state
 * The registers below target the good one in the arm7tdmi mass
 */
static struct opmode_regs regs_usr = {
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
static struct opmode_regs regs_fiq = {
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
static struct opmode_regs regs_irq = {
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
static struct opmode_regs regs_svc = {
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
static struct opmode_regs regs_abt = {
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
static struct opmode_regs regs_sys = {
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
static struct opmode_regs regs_und = {
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
 * When reset the machine, reset the registers
 */
void register_reset(void)
{
    memset(&arm7tdmi, 0x0, sizeof(struct arm7tdmi));
}

/**
 * In fact, owned by the core module
 * return a structure which describe the arm registers according to the processor operation
 */
struct opmode_regs *core_get_context_regs(void)
{
    switch (arm7tdmi.cpsr.opmode)
    {
        case OPERATION_MODE_USER:
            return (&regs_usr);
            break;
        case OPERATION_MODE_FIQ:
            return (&regs_fiq);
            break;
        case OPERATION_MODE_IRQ:
            return (&regs_irq);
            break;
        case OPERATION_MODE_SUPERVISOR:
            return (&regs_svc);
            break;
        case OPERATION_MODE_ABORT:
            return (&regs_abt);
            break;
        case OPERATION_MODE_SYSTEM:
            return (&regs_sys);
            break;
        case OPERATION_MODE_UNDEFINED:
            return (&regs_und);
            break;
        default:
            panic("Invalid operation mode");
    }
}

struct opmode_regs *core_get_opmode_regs(uint32_t mode)
{
    switch (mode)
    {
        case OPERATION_MODE_USER:
            return (&regs_usr);
            break;
        case OPERATION_MODE_FIQ:
            return (&regs_fiq);
            break;
        case OPERATION_MODE_IRQ:
            return (&regs_irq);
            break;
        case OPERATION_MODE_SUPERVISOR:
            return (&regs_svc);
            break;
        case OPERATION_MODE_ABORT:
            return (&regs_abt);
            break;
        case OPERATION_MODE_SYSTEM:
            return (&regs_sys);
            break;
        case OPERATION_MODE_UNDEFINED:
            return (&regs_und);
            break;
        default:
            panic("Invalid operation mode");
    }
}

/**
 * There are no rights consideration, the capcity to R/W must be decided before this function call.
 */
uint32_t *register_read_ptr(uint32_t id)
{
    if (id < 8)
        return (&(((uint32_t *)&arm7tdmi)[id]));
    switch (arm7tdmi.cpsr.opmode)
    {
        case OPERATION_MODE_USER:
            return (((uint32_t **)&regs_usr)[id]);
            break;
        case OPERATION_MODE_FIQ:
            return (((uint32_t **)&regs_fiq)[id]);
            break;
        case OPERATION_MODE_IRQ:
            return (((uint32_t **)&regs_irq)[id]);
            break;
        case OPERATION_MODE_SUPERVISOR:
            return (((uint32_t **)&regs_svc)[id]);
            break;
        case OPERATION_MODE_ABORT:
            return (((uint32_t **)&regs_abt)[id]);
            break;
        case OPERATION_MODE_SYSTEM:
            return (((uint32_t **)&regs_sys)[id]);
            break;
        case OPERATION_MODE_UNDEFINED:
            return (((uint32_t **)&regs_und)[id]);
            break;
        default:
            break;
    }
    panic("Invalid operation mode %d", arm7tdmi.cpsr.opmode);
}

/**
 * Read 8bits from the given BASE register
 */
uint8_t register_read8(uint32_t id)
{
    return (*(register_read_ptr(id)));
}

/**
 * Read 16bits from the given BASE register
 */
uint16_t register_read16(uint32_t id)
{
    return (*(register_read_ptr(id)));
}

/**
 * Read 32bits from the given BASE register
 */
uint32_t register_read32(uint32_t id)
{
    return (*(register_read_ptr(id)));
}

/**
 * Write 8bits to the given BASE register
 */
void register_write8(uint32_t id, uint8_t val)
{
    (*(register_read_ptr(id))) = val;
}

/**
 * Write 16bits to the given BASE register
 */
void register_write16(uint32_t id, uint16_t val)
{
    (*(register_read_ptr(id))) = val;
}

/**
 * Write 32bits to the given BASE register
 */
void register_write32(uint32_t id, uint32_t val)
{
    (*(register_read_ptr(id))) = val;
}

/**
 * Add the given value to the given BASE register
 */
void register_uadd32(uint32_t id, uint32_t val)
{
    uint32_t *r = register_read_ptr(id);
    (*r) += val;
}

/**
 * Add the given value to the given BASE register
 */
void register_usub32(uint32_t id, uint32_t val)
{
    uint32_t *r = register_read_ptr(id);
    (*r) -= val;
}

/**
 * Read the cpsr register, any operation mode
 */
struct register_psr register_read_cpsr(void)
{
    return (arm7tdmi.cpsr);
}

/**
 * Write the cpsr register, any operation mode
 */
void register_write_cpsr(uint32_t wr)
{
    arm7tdmi.cpsr.raw = wr;
}

/**
 * Read the spsr register according to the operation mode
 */
struct register_psr register_read_spsr(void)
{
    switch (arm7tdmi.cpsr.opmode)
    {
        case OPERATION_MODE_FIQ:
            return (*regs_usr.spsr);
            break;
        case OPERATION_MODE_IRQ:
            return (*regs_irq.spsr);
            break;
        case OPERATION_MODE_SUPERVISOR:
            return (*regs_svc.spsr);
            break;
        case OPERATION_MODE_ABORT:
            return (*regs_abt.spsr);
            break;
        case OPERATION_MODE_UNDEFINED:
            return (*regs_und.spsr);
            break;
        default:
            panic("Invalid operation mode");
    }
}

/**
 * Write the spsr register according to the operation mode
 */
void register_write_spsr(uint32_t wr)
{
    switch (arm7tdmi.cpsr.opmode)
    {
        case OPERATION_MODE_FIQ:
            (*regs_usr.spsr).raw = wr;
            break;
        case OPERATION_MODE_IRQ:
            (*regs_irq.spsr).raw = wr;
            break;
        case OPERATION_MODE_SUPERVISOR:
            (*regs_svc.spsr).raw = wr;
            break;
        case OPERATION_MODE_ABORT:
            (*regs_abt.spsr).raw = wr;
            break;
        case OPERATION_MODE_UNDEFINED:
            (*regs_und.spsr).raw = wr;
            break;
        default:
            panic("Invalid operation mode");
    }
}

/**
 * Read the cheated prefetch
 */
uint32_t core_read_prefetch(void)
{
    return (arm7tdmi.prefetch);
}

/**
 * Write the cheated prefetch
 */
void core_write_prefetch(uint32_t prefetch)
{
    arm7tdmi.prefetch = prefetch;
}

/**
 * Stop the CPU while running is false
 */
void core_cpu_stop_exec(void)
{
    arm7tdmi.running = false;
}

/**
 * Run the CPU while running is true
 */
void core_cpu_restart_exec(void)
{
    arm7tdmi.running = true;
}

/**
 * Read the running state
 */
bool core_cpu_read_exec_state(void)
{
    return (arm7tdmi.running);
}