/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "core/cycle/route.h"
# include "core/cycle/exec.h"

/**
 * https://pdf.dzsc.com/ARM/ARM7TDMI.pdf
 * page 108
 */
void *core_route_thumb(uint16_t op)
{
    switch (op >> 13)
    {
        case 0b000:
            if (bitfield_readx(op, 11, 13) == 0b11)
                (core_thumb_add_sub);
            else
                (core_thumb_shifts);
            goto err;
        case 0b001:
            (core_thumb_imm_op);
            goto err;
        case 0b010:
            if (bitfield_readx(op, 10, 13) == 0b000)
                (core_thumb_alu);
            else if (bitfield_readx(op, 10, 13) == 0b001)
                (core_thumb_reg_op);
            else if (bitfield_readx(op, 11, 13) == 0b01)
                (core_thumb_ldr_pc);
            else if (bitfield_read1(op, 12) == 0b1 && bitfield_read1(op, 9) == 0b0)
                (core_thumb_sdt_reg);
            else if (bitfield_read1(op, 12) == 0b1 && bitfield_read1(op, 9) == 0b1)
                (core_thumb_sdt_shw);
            goto err;
        case 0b011:
            (core_thumb_sdt_imm);
            goto err;
        case 0b100:
            if (bitfield_read1(op, 12) == 0b0)
                (core_thumb_sdt_hw);
            else
                (core_thumb_sdt_sp_rel);
            goto err;
        case 0b101:
            if (bitfield_read1(op, 12) == 0b0)
                (core_thumb_load_addr);
            else if (bitfield_readx(op, 8, 13) == 0b10000)
                (core_thumb_add_off_sp);
            else if (bitfield_readx(op, 9, 11) == 0b10 && bitfield_read1(op, 12) == 0b1)
                (core_thumb_push_pop_reg);
            goto err;
        case 0b110:
            if (bitfield_readx(op, 8, 13) == 0b11111)
                (core_thumb_swi);
            else if (bitfield_read1(op, 12) == 0b1)
                (core_thumb_cond_branch);
            else
                (core_thumb_mult_load_store);
            goto err;
        case 0b111:
            if (bitfield_read1(op, 12) == 0b0)
                (core_thumb_branch);
            else
                (core_thumb_branch_link);
            goto err;
        default:
            goto err;
    }
    err:
    panic("Invalid Opcode %#04x", op);
}