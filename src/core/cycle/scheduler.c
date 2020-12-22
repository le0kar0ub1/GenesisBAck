/******************************************************************************
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include "core/core.h"
# include "core/cycle/fetch.h"
# include "core/cycle/route.h"
# include "core/cycle/exec.h"

# define OPCODE_CONDITION_MASK(x) (x >> 28)

static void schedule_arm(void)
{
    uint32_t op;
    
    op = core_read_prefetch();
    core_write_prefetch(cycle_fetch_arm());
    register_uadd32(PC, 4);

    if (!schedule_opcode_condition(OPCODE_CONDITION_MASK(op)))
        return;
    cycle_route_arm(op);
}

static void schedule_thumb(void)
{
    uint32_t op;
    
    op = core_read_prefetch();
    core_write_prefetch((uint32_t)cycle_fetch_thumb());
    register_uadd32(PC, 2);
    cycle_route_thumb(op);
}

void core_scheduler(void)
{
    if (core_read_state() == PROCESSOR_STATE_ARM)
        schedule_arm();
    else
        schedule_thumb();
}

bool schedule_opcode_condition(uint32_t cond)
{
    struct register_psr cpsr = register_read_cpsr();

    switch (cond) {
        case CONDITION_EQ:
            return (cpsr.zero);
        case CONDITION_NE:
            return (!cpsr.zero);
        case CONDITION_CS:
            return (cpsr.carry);
        case CONDITION_CC:
            return (!cpsr.carry);
        case CONDITION_MI:
            return (cpsr.negative);
        case CONDITION_PL:
            return (!cpsr.negative);
        case CONDITION_VS:
            return (cpsr.overflow);
        case CONDITION_VC:
            return (!cpsr.overflow);
        case CONDITION_HI:
            return (cpsr.carry && !cpsr.zero);
        case CONDITION_LS:
            return (!cpsr.carry || cpsr.zero);
        case CONDITION_GE:
            return (cpsr.negative == cpsr.overflow);
        case CONDITION_LT:
            return (cpsr.negative != cpsr.overflow);
        case CONDITION_GT:
            return (!cpsr.zero && (cpsr.negative == cpsr.overflow));
        case CONDITION_LE:
            return (cpsr.zero || (cpsr.negative != cpsr.overflow));
        case CONDITION_AL: // unusable normaly
            return (true);
        case 1111: // obsolete never
        default:
            panic(__func__, "Invalid opcode condition %u", cond);
    }
}