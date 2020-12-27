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

void core_arm_coproc_data_operation(uint32_t op)
{
    uint32_t cp_op_reg = bitfield_readx(op, 0, 4);
    uint32_t cp_info = bitfield_readx(op, 5, 8);
    uint32_t cp_nb = bitfield_readx(op, 8, 12);
    uint32_t cp_dest_reg = bitfield_readx(op, 12, 16);
    uint32_t cp_op2_reg = bitfield_readx(op, 16, 20);
    uint32_t cp_opcode = bitfield_readx(op, 20, 24);

    panic("unimplemented");
}
