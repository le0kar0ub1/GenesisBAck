/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "core/exceptions.h"

struct exception_vector_trait
{
    uint32_t address;    // vector address
    uint32_t priority;   // priority compared to others ones
    uint32_t opmode;     // operation mode while taking the given exception
    bool is_irq_disable; // 1 if the flag irq_disable must be set, no action else 
    bool is_fiq_disable; // 1 if the flag fiq_disable must be set, no action else 
};

static struct exception_vector_trait reset_vector = {
    .address  = EXCEPTION_RESET,
    .priority = 1,
    .opmode = OPERATION_MODE_SUPERVISOR,
    .is_irq_disable = true,
    .is_fiq_disable = true
};

static struct exception_vector_trait und_instr_vector = {
    .address  = EXCEPTION_UND_INSTR,
    .priority = 7,
    .opmode = OPERATION_MODE_UNDEFINED,
    .is_irq_disable = true,
    .is_fiq_disable = false
};

static struct exception_vector_trait swi_vector = {
    .address  = EXCEPTION_SWI,
    .priority = 6,
    .opmode = OPERATION_MODE_SUPERVISOR,
    .is_irq_disable = true,
    .is_fiq_disable = false
};

static struct exception_vector_trait prefetch_abt_vector = {
    .address  = EXCEPTION_PREFETCH_ABT,
    .priority = 5,
    .opmode = OPERATION_MODE_ABORT,
    .is_irq_disable = true,
    .is_fiq_disable = false
};

static struct exception_vector_trait data_abt_vector = {
    .address  = EXCEPTION_DATA_ABT,
    .priority = 2,
    .opmode = OPERATION_MODE_ABORT,
    .is_irq_disable = true,
    .is_fiq_disable = false
};

static struct exception_vector_trait addr_exceed_vector = {
    .address  = EXCEPTION_ADDR_EXCEED,
    .priority = -1,
    .opmode = OPERATION_MODE_SUPERVISOR,
    .is_irq_disable = true,
    .is_fiq_disable = false
};

static struct exception_vector_trait irq_vector = {
    .address  = EXCEPTION_IRQ,
    .priority = 4,
    .opmode = OPERATION_MODE_IRQ,
    .is_irq_disable = true,
    .is_fiq_disable = false
};

static struct exception_vector_trait fiq_vector = {
    .address  = EXCEPTION_FIQ,
    .priority = 3,
    .opmode = OPERATION_MODE_FIQ,
    .is_irq_disable = true,
    .is_fiq_disable = true
};

static inline struct exception_vector_trait cpu_fetch_exception_vector_trait(enum EXCEPTION_VECTOR vector)
{
    switch (vector)
    {
        case EXCEPTION_RESET:
            return (reset_vector);
            break;
        case EXCEPTION_UND_INSTR:
            return (und_instr_vector);
            break;
        case EXCEPTION_SWI:
            return (swi_vector);
            break;
        case EXCEPTION_PREFETCH_ABT:
            return (prefetch_abt_vector);
            break;
        case EXCEPTION_DATA_ABT:
            return (data_abt_vector);
            break;
        case EXCEPTION_ADDR_EXCEED:
            return (addr_exceed_vector);
            break;
        case EXCEPTION_IRQ:
            return (irq_vector);
            break;
        case EXCEPTION_FIQ:
            return (fiq_vector);
            break;
        default:
            return (reset_vector);
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
    struct exception_vector_trait vec = cpu_fetch_exception_vector_trait(vector);

    /* New opmode  */
    new_cpsr.opmode = vec.opmode;
    register_write_cpsr(new_cpsr.raw);
    /* Save old cpsr */
    register_write_spsr(old_cpsr.raw);
    /* Link register to current address */
    register_write32(LR, pc);
    /* update CPSR */
    new_cpsr.state = STATE_ARM;
    new_cpsr.irq_disable = true;
    if (vec.is_fiq_disable == true)
        new_cpsr.fiq_disable = true;
    register_write_cpsr(new_cpsr.raw);
    /* Set PC to vector address */
    register_write32(PC, vec.address);
    panic("Must reload pipeline");
}

/**
 * Used by the cpu to raise an exception, all the need (for the switch) is handled here
 */
void exception_raise(enum EXCEPTION_VECTOR vector)
{
    LOG_INF("raising exception %d", vector);
    exception_perform_entry(vector);
}