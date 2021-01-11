/******************************************************************************
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include "core/core.h"
# include "mmu/mmu.h"
# include "gba/cartridge.h"
# include "modules/module.h"
# include "debug/debug.h"

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

/**
 * Flush/Reload the pipeline
 */
void core_flush_pipeline(void)
{
    uint32_t pc = register_read32(PC);

    if (core_read_state() == STATE_ARM) {
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

static void core_reset(void)
{
    struct opmode_regs *usr = core_get_opmode_regs(OPERATION_MODE_USER);
    struct opmode_regs *sys = core_get_opmode_regs(OPERATION_MODE_SYSTEM);
    struct opmode_regs *irq = core_get_opmode_regs(OPERATION_MODE_IRQ);
    struct opmode_regs *svc = core_get_opmode_regs(OPERATION_MODE_SUPERVISOR);

    register_reset();

    *(usr->r13) = 0x3007F00;
    *(sys->r13) = 0x3007F00;
    *(irq->r13) = 0x3007FA0;
    *(svc->r13) = 0x3007FE0;

    *(sys->r15) = cartridge_get_entry_point();
    core_switch_opmode(OPERATION_MODE_SYSTEM);
    core_switch_state(STATE_ARM);

    core_flush_pipeline();
    core_cpu_restart_exec();
}

/**
 * Start the execution
 */
static void core_start(void)
{
    while (1) {
        core_scheduler();
    }
}

static void core_init(void)
{
    core_reset();
}

static void core_exit(void) {}

static void core_info(void)
{
#if ROUTINE == ROUTINE_DEBUG
    debug_cmd_regs(1, NULL);
#endif
}

REGISTER_MODULE(
    core,
    "The core of the emulator which schedule the RELEASE execution",
    MODULE_HOOK_CORE,
    core_init,
    core_exit,
    core_reset,
    core_start,
    NULL,
    core_info
);