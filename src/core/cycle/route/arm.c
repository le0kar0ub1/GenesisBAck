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

void *cycle_route_arm(uint32_t op)
{
    switch (bitfld_readx(op, 25, 27))
    {
        case 0b00:
            if (bitfld_read1(op, 25) == 0b1 || (bitfld_read1(op, 25) == 0 && bitfld_readx(op, 4, 12) == 0b0))
                return (core_arm_data_processing);
            if ((bitfld_readx(op, 22, 26) == 0b0000 || bitfld_readx(op, 23, 26) == 0b001) && bitfld_readx(op, 4, 8) == 0b1001)
                return (core_arm_multiply);
            else if (bitfld_readx(op, 4, 26) == 0b010010111111111111000)
                return (core_arm_branch_exchange);
            else if (bitfld_readx(op, 7, 12) == 0b00001 && bitfld_read1(op, 4) == 0b1 && bitfld_read1(op, 22) == 0b0 && bitfld_read1(op, 25) == 0b0)
                return (core_arm_reg_data_transfer);
            else if (bitfld_read1(op, 4) == 0b1 && bitfld_read1(op, 7) == 0b1 && bitfld_read1(op, 22) == 0b1 && bitfld_read1(op, 25) == 0b0)
                return (core_arm_imm_data_transfer);
            break;
        case 0b01:
            if (bitfld_read1(op, 25) == 0b1 && bitfld_read1(op, 4) == 0b1)
                return (core_arm_undefined);
            else
                return (core_arm_single_data_transfer);
            break;
        case 0b10:
            if (bitfld_read1(op, 25) == 0b0)
                return (core_arm_block_data_trabsfer);
            else
                return (core_arm_branch);
            break;
        case 0b11:
            if (bitfld_read1(op, 25) == 0b0)
                return (core_arm_coprocessor_data_transfer);
            else if (bitfld_readx(op, 24, 26) == 0b10 && bitfld_read1(op, 4) == 0b0)
                return (core_arm_coprocessor_data_operation);
            else if (bitfld_readx(op, 24, 26) == 0b10 && bitfld_read1(op, 4) == 0b1)
                return (core_arm_coprocessor_register_transfer);
            else if (bitfld_readx(op, 24, 26) == 0b11)
                return (core_arm_swi);
            break;
        default:
            panic(__func__, "Invalid Opcode %u", op);
    }
    panic(__func__, "Invalid Opcode %u", op);
}