/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <core/cycle/exec.h>
# include <mmu/mmu.h>

void core_arm_sgl_dataswap(uint32_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rm = bitfield_readx(op, 0, 4);
    uint32_t rd = bitfield_readx(op, 12, 16);
    uint32_t rn = bitfield_readx(op, 16, 20);
    uint32_t swapaddr = *(regs->raw[rn]);
    uint32_t buf;

    if (!bitfield_read1(op, 22)) { // byte
        buf = (uint32_t)mmu_read8(swapaddr);
        mmu_write8(swapaddr, (uint8_t)*(regs->raw[rm]));
        *(regs->raw[rd]) = buf;
    } else { // word
        buf = mmu_read32(swapaddr);
        mmu_write32(swapaddr, *(regs->raw[rm]));
        *(regs->raw[rd]) = buf;
    }
}