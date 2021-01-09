/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "gba/cartridge.h" 
# include "core/exceptions.h"

struct exception_vector_trait
{
    char const *name;
    uint32_t address;    // vector address
    uint32_t priority;   // priority compared to others ones
    uint32_t opmode;     // operation mode while taking the given exception
    bool is_irq_disable; // 1 if the flag irq_disable must be set, no action else 
    bool is_fiq_disable; // 1 if the flag fiq_disable must be set, no action else 
    bool emulator_panic;
};

# define REGISTER_VECTOR(xdef, xpriority, xopmode, xirq, xfiq, xpanic)   \
    [xdef / 4] = {                                                       \
        .name = #xdef,                                                   \
        .address  = xdef,                                                \
        .priority = xpriority,                                           \
        .opmode = xopmode,                                               \
        .is_irq_disable = xirq,                                          \
        .is_fiq_disable = xfiq,                                          \
        .emulator_panic = xpanic                                         \
    }

static struct exception_vector_trait vectors[] = {
    REGISTER_VECTOR(
        EXCEPTION_RESET, 1, OPERATION_MODE_SUPERVISOR, true, true, true
    ),
    REGISTER_VECTOR(
        EXCEPTION_UND_INSTR, 7, OPERATION_MODE_UNDEFINED, true, false, true
    ),
    REGISTER_VECTOR(
        EXCEPTION_SWI, 6, OPERATION_MODE_SUPERVISOR, true, false, false
    ),
    REGISTER_VECTOR(
        EXCEPTION_PREFETCH_ABT, 5, OPERATION_MODE_ABORT, true, false, true
    ),
    REGISTER_VECTOR(
        EXCEPTION_DATA_ABT, 2, OPERATION_MODE_ABORT, true, false, true
    ),
    REGISTER_VECTOR(
        EXCEPTION_ADDR_EXCEED, 1, OPERATION_MODE_SUPERVISOR, true, false, true
    ),
    REGISTER_VECTOR(
        EXCEPTION_IRQ, 4, OPERATION_MODE_IRQ, true, false, true
    ),
    REGISTER_VECTOR(
        EXCEPTION_FIQ, 3, OPERATION_MODE_FIQ, true, true, true
    )
};

#undef REGISTER_VECTOR

static inline struct exception_vector_trait *exception_fetch_vector_trait(enum EXCEPTION_VECTOR vector)
{
    if (vector / 4 < (sizeof(vectors) / sizeof(struct exception_vector_trait))) {
        return (&vectors[vector / 4]);
    } else {
        panic("Invalid exception vector");
    }
}

/**
 * Perform an exception entry: sequence of save
 * No priority handling,
 */
static void exception_perform_entry(enum EXCEPTION_VECTOR vector)
{
    /*
    - R14_<new mode>=PC+nn   ;save old PC, ie. return address
    - SPSR_<new mode>=CPSR   ;save old flags
    - CPSR new T,M bits      ;set to T=0 (ARM state), and M4-0=new mode
    - CPSR new I bit         ;IRQs disabled (I=1), done by ALL exceptions
    - CPSR new F bit         ;FIQs disabled (F=1), done by Reset and FIQ only
    - PC=exception_vector    ;see table above
    */
    uint32_t pc = (uint32_t)register_read32(PC);
    struct register_psr old_cpsr = register_read_cpsr();
    struct register_psr new_cpsr = old_cpsr;
    struct exception_vector_trait *vec = exception_fetch_vector_trait(vector);

    /* New opmode  */
    new_cpsr.opmode = vec->opmode;
    register_write_cpsr(new_cpsr.raw);
    /* Save old cpsr */
    register_write_spsr(old_cpsr.raw);
    /* Link register to current address */
    register_write32(LR, pc);
    /* update CPSR */
    new_cpsr.state = STATE_ARM;
    new_cpsr.irq_disable = true;
    if (vec->is_fiq_disable == true)
        new_cpsr.fiq_disable = true;
    register_write_cpsr(new_cpsr.raw);
    /* Set PC to vector address */
    register_write32(PC, cartridge_get_entry_point() + vec->address);
    core_flush_pipeline();
}

/**
 * Used by the cpu to raise an exception, all the need (for the switch) is handled here
 */
void exception_raise(enum EXCEPTION_VECTOR vector, uint32_t hdl)
{
    if (exception_fetch_vector_trait(vector)->emulator_panic)
        panic("Exception %s make panicked", exception_fetch_vector_trait(vector)->name);
    exception_perform_entry(vector);
}