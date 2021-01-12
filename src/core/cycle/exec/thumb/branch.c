/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <core/cycle/exec.h>

void core_thumb_cond_branch(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    int32_t off = ((int32_t)(int8_t)bitfield_readx(op, 0, 8)) << 1;
    
    if (schedule_opcode_condition(bitfield_readx(op, 8, 12))) {
        *(regs->r15) += off;
        core_flush_pipeline();
    }
}

void core_thumb_branch(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    int32_t off = sign_extend11_to_i32(bitfield_readx(op, 0, 11) << 1);
    
    *(regs->r15) += off;
    core_flush_pipeline();
}

void core_thumb_branch_link(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t off = bitfield_readx(op, 0, 11);
    uint32_t lr;
    bool h = bitfield_read1(op, 11);

    if (h) {
        lr = *(regs->r14) + (off << 1);
        *(regs->r14) = (*(regs->r15) - 2) | 0b1;
        *(regs->r15) = lr;
        core_flush_pipeline();
    } else {
        *(regs->r14) = *(regs->r15) + (sign_extend11_to_i32(off) << 12);
    }
}
