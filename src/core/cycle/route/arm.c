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
            if (bitfield_read1(op, 25) == 0b1 || (bitfield_read1(op, 25) == 0 && bitfield_readx(op, 4, 12) == 0b0))
                {ROUTE_RETURN (core_arm_data_processing);}
            else if ((bitfield_readx(op, 22, 26) == 0b0000 || bitfield_readx(op, 23, 26) == 0b001) && bitfield_readx(op, 4, 8) == 0b1001)
                {ROUTE_RETURN (core_arm_multiply);}
            else if (bitfield_readx(op, 4, 26) == 0b010010111111111111000)
                {ROUTE_RETURN (core_arm_branch_exchange);}
            else if (bitfield_readx(op, 7, 12) == 0b00001 && bitfield_read1(op, 4) == 0b1 && bitfield_read1(op, 22) == 0b0 && bitfield_read1(op, 25) == 0b0)
                {ROUTE_RETURN (core_arm_reg_data_transfer);}
            else if (bitfield_read1(op, 4) == 0b1 && bitfield_read1(op, 7) == 0b1 && bitfield_read1(op, 22) == 0b1 && bitfield_read1(op, 25) == 0b0)
                {ROUTE_RETURN (core_arm_imm_data_transfer);}
            goto err;
        case 0b01:
            if (bitfield_read1(op, 25) == 0b1 && bitfield_read1(op, 4) == 0b1)
                {ROUTE_RETURN (core_arm_undefined);}
            else
                {ROUTE_RETURN (core_arm_single_data_transfer);}
            goto err;
        case 0b10:
            if (bitfield_read1(op, 25) == 0b0)
                {ROUTE_RETURN (core_arm_block_data_trabsfer);}
            else
                {ROUTE_RETURN (core_arm_branch);}
            goto err;
        case 0b11:
            if (bitfield_read1(op, 25) == 0b0)
                {ROUTE_RETURN (core_arm_coprocessor_data_transfer);}
            else if (bitfield_readx(op, 24, 26) == 0b10 && bitfield_read1(op, 4) == 0b0)
                {ROUTE_RETURN (core_arm_coprocessor_data_operation);}
            else if (bitfield_readx(op, 24, 26) == 0b10 && bitfield_read1(op, 4) == 0b1)
                {ROUTE_RETURN (core_arm_coprocessor_register_transfer);}
            else if (bitfield_readx(op, 24, 26) == 0b11)
                {ROUTE_RETURN (core_arm_swi);}
            goto err;
        default:
            goto err;
    }
    err:
    panic("Invalid Opcode %#x", op);
}