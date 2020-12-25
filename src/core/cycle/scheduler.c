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
    void *(*handler)(uint32_t);
    
    op = core_read_prefetch();
    LOG_DEBUG("Running instruction %#x", op);
    core_write_prefetch(core_fetch_arm());
    register_uadd32(PC, 4);

    if (!schedule_opcode_condition(OPCODE_CONDITION_MASK(op)))
        return;
    handler = core_route_arm(op);
    handler(op);
}

static void schedule_thumb(void)
{
    uint16_t op;
    void *(*handler)(uint16_t);
    
    op = (uint16_t)core_read_prefetch();
    LOG_DEBUG("Running instruction %#x", op);
    core_write_prefetch((uint32_t)core_fetch_thumb());
    register_uadd32(PC, 2);

    handler = core_route_thumb(op);
    handler(op);
}

void core_scheduler(void)
{
    if (core_read_state() == STATE_ARM)
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
            panic("Invalid opcode condition %u", cond);
    }
}