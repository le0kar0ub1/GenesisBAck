/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "core/core.h"
# include "core/cycle/exec.h"

void core_arm_data_processing(uint32_t op)
{
    struct arm_regs *regs = core_get_arm_regs();
    uint32_t rd = (op >> 12) & 0xF;
    uint32_t rn = (op >> 16) & 0xF;
    uint32_t op1 = *(regs->raw[rn]);
    uint32_t op2;
    bool condition = bitfield_read1(op, 20);

    if (bitfield_read1(op, 25) == 0b0) {

    } else {
        
    }


    switch (bitfield_readx(op, 21, 25))
    {
        case 0b0000:
            break;
        case 0b0001:
            break;
        case 0b0010:
            break;
        case 0b0011:
            break;
        case 0b0100:
            break;
        case 0b0101:
            break;
        case 0b0110:
            break;
        case 0b0111:
            break;
        case 0b1000:
            break;
        case 0b1001:
            break;
        case 0b1010:
            break;
        case 0b1011:
            break;
        case 0b1100:
            break;
        case 0b1101:
            break;
        case 0b1110:
            break;
        case 0b1111:
            break;
        default:
            break;
    }
}
