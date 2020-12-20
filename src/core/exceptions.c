/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "core/exceptions.h"

static struct cpu_exception_vector_trait reset_vector = {
    .address  = EXCEPTION_RESET,
    .priority = 1,
    .opmode = PROCESSOR_OPERATION_MODE_SUPERVISOR,
    .is_irq_disable = true,
    .is_fiq_disable = true
};

static struct cpu_exception_vector_trait und_instr_vector = {
    .address  = EXCEPTION_UND_INSTR,
    .priority = 7,
    .opmode = PROCESSOR_OPERATION_MODE_UNDEFINED,
    .is_irq_disable = true,
    .is_fiq_disable = false
};

static struct cpu_exception_vector_trait swi_vector = {
    .address  = EXCEPTION_SWI,
    .priority = 6,
    .opmode = PROCESSOR_OPERATION_MODE_SUPERVISOR,
    .is_irq_disable = true,
    .is_fiq_disable = false
};

static struct cpu_exception_vector_trait prefetch_abt_vector = {
    .address  = EXCEPTION_PREFETCH_ABT,
    .priority = 5,
    .opmode = PROCESSOR_OPERATION_MODE_ABORT,
    .is_irq_disable = true,
    .is_fiq_disable = false
};

static struct cpu_exception_vector_trait data_abt_vector = {
    .address  = EXCEPTION_DATA_ABT,
    .priority = 2,
    .opmode = PROCESSOR_OPERATION_MODE_ABORT,
    .is_irq_disable = true,
    .is_fiq_disable = false
};

static struct cpu_exception_vector_trait addr_exceed_vector = {
    .address  = EXCEPTION_ADDR_EXCEED,
    .priority = -1,
    .opmode = PROCESSOR_OPERATION_MODE_SUPERVISOR,
    .is_irq_disable = true,
    .is_fiq_disable = false
};

static struct cpu_exception_vector_trait irq_vector = {
    .address  = EXCEPTION_IRQ,
    .priority = 4,
    .opmode = PROCESSOR_OPERATION_MODE_IRQ,
    .is_irq_disable = true,
    .is_fiq_disable = false
};

static struct cpu_exception_vector_trait fiq_vector = {
    .address  = EXCEPTION_FIQ,
    .priority = 3,
    .opmode = PROCESSOR_OPERATION_MODE_FIQ,
    .is_irq_disable = true,
    .is_fiq_disable = true
};

static inline struct cpu_exception_vector_trait cpu_fetch_exception_vector_trait(enum EXCEPTION_VECTOR vector)
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
static void cpu_exception_perform_entry(enum EXCEPTION_VECTOR vector)
{
    /*
    - R14_<new mode>=PC+nn   ;save old PC, ie. return address
    - SPSR_<new mode>=CPSR   ;save old flags
    - CPSR new T,M bits      ;set to T=0 (ARM state), and M4-0=new mode
    - CPSR new I bit         ;IRQs disabled (I=1), done by ALL exceptions
    - CPSR new F bit         ;FIQs disabled (F=1), done by Reset and FIQ only
    - PC=exception_vector    ;see table above
    */
    uint32_t pc = (uint32_t)fetch_register_base32(PC);
    struct arm7tdmi_psr cpsr = fetch_register_cpsr();
    struct cpu_exception_vector_trait vec = cpu_fetch_exception_vector_trait(vector);
    assign_processor_opmode(vec.opmode);
    assign_register_spsr(cpsr);
    assign_register_base32(LR, pc + (fetch_processor_state() == PROCESSOR_STATE_ARM ? 4 : 2));
    cpsr.opmode = vec.opmode;
    cpsr.state = PROCESSOR_STATE_ARM;
    cpsr.irq_disable = true;
    if (vec.is_fiq_disable == true)
        cpsr.fiq_disable = true;
    assign_register_cpsr(cpsr);
    assign_register_base32(PC, vec.address);
}

/**
 * Used by the cpu to raise an exception, all the need (for the switch) is handled here
 */
void cpu_exception_raise(enum EXCEPTION_VECTOR vector)
{
    LOG_INF(exception, "raising exception %d", vector);
    cpu_exception_perform_entry(vector);
}