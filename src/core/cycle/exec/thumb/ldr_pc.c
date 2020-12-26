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

void core_thumb_ldr_pc(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t imm = bitfield_readx(op, 0, 8) << 2;
    uint32_t rd = bitfield_readx(op, 8, 11);

    *(regs->raw[rd]) = mmu_read32(regs->r15->r32 + imm);
}