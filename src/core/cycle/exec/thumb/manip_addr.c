/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "core/cycle/exec.h"
# include "mmu/mmu.h"

void core_thumb_load_addr(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t off = bitfield_readx(op, 0, 8) << 2;
    uint32_t rd = bitfield_readx(op, 8, 11);

    if (!bitfield_read1(op, 11)) {
        *(regs->raw[rd]) = regs->r15->r32 + off;
    } else {
        *(regs->raw[rd]) = regs->r13->r32 + off;
    }
}

void core_thumb_add_off_sp(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t off = bitfield_readx(op, 0, 7) << 2;

    if (!bitfield_read1(op, 7)) {
        regs->r13->r32 += off;
    } else {
        regs->r13->r32 -= off;
    }
}