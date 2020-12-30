/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "core/cycle/exec.h"

void core_arm_branch_exchange(uint32_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t addr = *(regs->raw[op & 0xF]);

    (*(regs->r15)).r32 = ALIGN2(addr);
    (*(regs->cpsr)).state = addr & 0b1;
    core_flush_pipeline();
}

void core_arm_branch(uint32_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    int32_t off = sign_extend24_to_i32(op & 0xFFFFFF) << 2;

    if (bitfield_read1(op, 24) == 0b1)
        (*(regs->r14)).r32 = (*(regs->r15)).r32 - 4; // the current instruction

    (*(regs->r15)).r32 += off;
    core_flush_pipeline();   
}