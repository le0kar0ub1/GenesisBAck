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

void core_arm_reg_hfdt(uint32_t op)
{
    panic("unimplemented");
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rm = bitfield_readx(op, 0, 4);
    uint32_t rd = (op >> 12) & 0xF;
    uint32_t rn = (op >> 16) & 0xF;
    uint32_t base = *(regs->raw[rn]);
    bool load = bitfield_read1(op, 20);
    bool writeback = bitfield_read1(op, 21);
    bool updown = bitfield_read1(op, 23);
    bool indexing = bitfield_read1(op, 24);
    uint32_t addr;
    uint32_t wbaddr;
}

void core_arm_imm_hfdt(uint32_t op)
{
    panic("unimplemented");
}

void core_arm_block_dt(uint32_t op)
{
    panic("unimplemented");
}

void core_arm_coproc_dt(uint32_t op)
{
    panic("unimplemented");
}

void core_arm_coproc_data_operation(uint32_t op)
{
    panic("unimplemented");
}

void core_arm_coproc_register_transfer(uint32_t op)
{
    panic("unimplemented");
}
