/******************************************************************************
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include "core/core.h"
# include "mmu/mmu.h"

uint32_t core_read_state(void)
{
    return (register_read_cpsr().state);
}

uint32_t core_read_opmode(void)
{
    return (register_read_cpsr().opmode);
}

void core_switch_state(uint32_t state)
{
    struct register_psr cpsr = register_read_cpsr();
    cpsr.state = state;
    register_write_cpsr(cpsr.raw);
}

void core_switch_opmode(uint32_t opmode)
{
    struct register_psr cpsr = register_read_cpsr();
    cpsr.opmode = opmode;
    register_write_cpsr(cpsr.raw);
}

void core_init(void)
{
    core_reset();
}

void core_reset(void)
{
    register_reset();
    core_switch_opmode(PROCESSOR_OPERATION_MODE_SYSTEM);
    register_write32(PC, 0x8000000);
    register_write32(SP, 0x3007F00);
    core_reload_pipeline();
}

void core_start(void)
{
    while (1)
        core_scheduler();
}

void core_reload_pipeline(void)
{
    uint32_t pc = register_read32(PC);

    if (core_read_state() == PROCESSOR_STATE_ARM) {
        pc = MASK_ARM_RELOAD(pc);
        core_write_prefetch(mmu_read32(pc));
        pc += 4;
        register_write32(PC, pc);
    } else {
        pc = MASK_THUMB_RELOAD(pc);
        core_write_prefetch(mmu_read16(pc));
        pc += 2;
        register_write32(PC, pc);
    }
}