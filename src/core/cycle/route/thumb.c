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
    switch (op >> 12)
    {
        case 0b000:
            if (bitfld_readx(op, 11, 13) == 0b11)
                {ROUTE_RETURN (core_thumb_add_sub);}
            else
                {ROUTE_RETURN (core_thumb_mv_shifted_reg);}
            goto err;
        case 0b001:
            {ROUTE_RETURN (core_thumb_imm_op);}
            goto err;
        case 0b010:
            if (bitfld_readx(op, 10, 13) == 0b000)
                {ROUTE_RETURN (core_thumb_alu_op);}
            else if (bitfld_readx(op, 12, 13) == 0b001)
                {ROUTE_RETURN (core_thumb_hireg_op_br_exch);}
            else if (bitfld_readx(op, 11, 13) == 0b01)
                {ROUTE_RETURN (core_thumb_pc_rel_load);}
            else if (bitfld_read1(op, 12) == 0b1 && bitfld_read1(op, 9) == 0b0)
                {ROUTE_RETURN (core_thumb_reg_off_load_store);}
            else if (bitfld_read1(op, 12) == 0b1 && bitfld_read1(op, 9) == 0b1)
                {ROUTE_RETURN (core_thumb_sign_ext_load_store);}
            goto err;
        case 0b011:
            {ROUTE_RETURN (core_thumb_immoff_load_store);}
            goto err;
        case 0b100:
            if (bitfld_read1(op, 12) == 0b0)
                {ROUTE_RETURN (core_thumb_hf_load_store);}
            else
                {ROUTE_RETURN (core_thumb_sp_rel_load_store);}
            goto err;
        case 0b101:
            if (bitfld_read1(op, 12) == 0b0)
                {ROUTE_RETURN (core_thumb_load_addr);}
            else if (bitfld_readx(op, 8, 13) == 0b10000)
                {ROUTE_RETURN (core_thumb_add_off_sp);}
            else if (bitfld_readx(op, 9, 11) == 0b10 && bitfld_read1(op, 12) == 0b1)
                {ROUTE_RETURN (core_thumb_push_pop_reg);}
            goto err;
        case 0b110:
            if (bitfld_readx(op, 8, 13) == 0b11111)
                {ROUTE_RETURN (core_thumb_swi);}
            else if (bitfld_read1(op, 12) == 0b1)
                {ROUTE_RETURN (core_thumb_conditional_branch);}
            else
                {ROUTE_RETURN (core_thumb_mult_load_store);}
            goto err;
        case 0b111:
            if (bitfld_read1(op, 12) == 0b0)
                {ROUTE_RETURN (core_thumb_unconditional_branch);}
            else
                {ROUTE_RETURN (core_thumb_branch_link);}
            goto err;
        default:
            goto err;
    }
    err:
    panic(__func__, "Invalid Opcode %u", op);
}