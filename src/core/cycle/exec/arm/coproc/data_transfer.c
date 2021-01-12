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

void core_arm_coproc_data_transfer(uint32_t op)
{
    uint32_t off = bitfield_readx(op, 0, 8);
    uint32_t cp_nb = bitfield_readx(op, 8, 12);
    uint32_t cp_reg = bitfield_readx(op, 12, 16);
    uint32_t cp_rbase = bitfield_readx(op, 16, 20);

    panic("unimplemented");
}