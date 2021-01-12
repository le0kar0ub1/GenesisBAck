/******************************************************************************
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include "core/core.h"
# include <pthread.h>
# include <string.h>

static pthread_mutex_t mutex;
bool running;

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
};

/**
 * The totality of the ar7tdmi registers
 */
static struct arm7tdmi arm7tdmi;

# define OPMODE_MASK(x) (x & 0b01111)

static struct opmode_regs regs[] = {
    [0x0 ... 0x10] = {
        .r0   = NULL,
        .r1   = NULL,
        .r2   = NULL,
        .r3   = NULL,
        .r4   = NULL,
        .r5   = NULL,
        .r6   = NULL,
        .r7   = NULL,
        .r8   = NULL,
        .r9   = NULL,
        .r10  = NULL,
        .r11  = NULL,
        .r12  = NULL,
        .r13  = NULL,
        .r14  = NULL,
        .r15  = NULL,
        .cpsr = NULL,
        .spsr = NULL
    },
    [OPMODE_MASK(OPERATION_MODE_USER)] = {
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
    },
    [OPMODE_MASK(OPERATION_MODE_FIQ)] = {
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
    },
    [OPMODE_MASK(OPERATION_MODE_IRQ)] = {
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
    },
    [OPMODE_MASK(OPERATION_MODE_SUPERVISOR)] = {
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
    },
    [OPMODE_MASK(OPERATION_MODE_ABORT)] = {
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
    },
    [OPMODE_MASK(OPERATION_MODE_UNDEFINED)] = {
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
    },
    [OPMODE_MASK(OPERATION_MODE_SYSTEM)] = {
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
    }
};

struct opmode_regs *core_get_opmode_regs(uint32_t mode)
{
    if (!regs[OPMODE_MASK(mode)].r0)
        panic("Invalid operation mode");
    else
        return (&regs[OPMODE_MASK(mode)]);
}

#undef OPMODE_MASK

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
    return (core_get_opmode_regs(arm7tdmi.cpsr.opmode));
}

/**
 * There are no rights consideration, the capacity to R/W must be decided before this function call.
 */
static uint32_t *register_read_ptr(uint32_t id)
{
    return (core_get_context_regs()->raw[id]);
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
    struct opmode_regs *r = core_get_context_regs();

    if (r->spsr)
        return (*(r->spsr));
    else
        panic("Invalid operation mode");
}

/**
 * Write the spsr register according to the operation mode
 */
void register_write_spsr(uint32_t wr)
{
    struct opmode_regs *r = core_get_context_regs();

    if (r->spsr)
        r->spsr->raw = wr;
    else
        panic("Invalid operation mode");
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
    running = false;
}

/**
 * Run the CPU while running is true
 */
void core_cpu_restart_exec(void)
{
    running = true;
}

/**
 * Read the running state
 */
bool core_cpu_read_exec_state(void)
{
    return (running);
}