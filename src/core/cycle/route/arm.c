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
 * page 44
 */
void *core_route_arm(uint32_t op)
{
    switch (bitfield_readx(op, 26, 28))
    {
        case 0b00:
            if (bitfield_readx(op, 23, 26) == 0b010 && bitfield_readx(op, 16, 22) == 0b001111 && bitfield_readx(op, 0, 12) == 0)
                {ROUTE_RETURN (core_arm_mrs);}
            else if (bitfield_readx(op, 23, 26) == 0b010 && bitfield_readx(op, 12, 22) == 0b1010011111 && bitfield_readx(op, 4, 12) == 0)
                {ROUTE_RETURN (core_arm_msr);}
            else if (bitfield_readx(op, 23, 25) == 0b10 && bitfield_readx(op, 12, 22) == 0b1010001111)
                {ROUTE_RETURN (core_arm_msrf);}
            else if (bitfield_readx(op, 22, 26) == 0b0000 && bitfield_readx(op, 4, 8) == 0b1001)
                {ROUTE_RETURN (core_arm_multiply);}
            else if (bitfield_readx(op, 23, 26) == 0b001 && bitfield_readx(op, 4, 8) == 0b1001)
                {ROUTE_RETURN (core_arm_multiply_long);}
            else if (bitfield_readx(op, 4, 12) == 0b00001001 && bitfield_readx(op, 20, 22) == 0b00 && bitfield_readx(op, 23, 26) == 0b010)
                {ROUTE_RETURN (core_arm_sgl_dataswap);}
            else if (bitfield_readx(op, 4, 26) == 0b0100101111111111110001)
                {ROUTE_RETURN (core_arm_branch_exchange);}
            else if (bitfield_readx(op, 7, 12) == 0b00001 && bitfield_read1(op, 4) == 0b1 && bitfield_read1(op, 22) == 0b0 && bitfield_read1(op, 25) == 0b0)
                {ROUTE_RETURN (core_arm_reg_hwdt);}
            else if (bitfield_read1(op, 4) == 0b1 && bitfield_read1(op, 7) == 0b1 && bitfield_read1(op, 22) == 0b1 && bitfield_read1(op, 25) == 0b0)
                {ROUTE_RETURN (core_arm_imm_hwdt);}
            else if (bitfield_read1(op, 4) == 0b0 || bitfield_read1(op, 7) == 0b0)
                {ROUTE_RETURN (core_arm_alu);}
            goto err;
        case 0b01:
            if (bitfield_read1(op, 25) == 0b1 && bitfield_read1(op, 4) == 0b1)
                {ROUTE_RETURN (core_arm_undefined);}
            else
                {ROUTE_RETURN (core_arm_single_dt);}
            goto err;
        case 0b10:
            if (bitfield_read1(op, 25) == 0b0)
                {ROUTE_RETURN (core_arm_block_dt);}
            else
                {ROUTE_RETURN (core_arm_branch);}
            goto err;
        case 0b11:
            if (bitfield_read1(op, 25) == 0b0)
                {ROUTE_RETURN (core_arm_coproc_data_transfer);}
            else if (bitfield_readx(op, 24, 26) == 0b10 && bitfield_read1(op, 4) == 0b0)
                {ROUTE_RETURN (core_arm_coproc_data_operation);}
            else if (bitfield_readx(op, 24, 26) == 0b10 && bitfield_read1(op, 4) == 0b1)
                {ROUTE_RETURN (core_arm_coproc_register_transfer);}
            else if (bitfield_readx(op, 24, 26) == 0b11)
                {ROUTE_RETURN (core_arm_swi);}
            goto err;
        default:
            goto err;
    }
    err:
    panic("Invalid Opcode %#x", op);
}