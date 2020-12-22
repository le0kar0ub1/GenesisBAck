/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "core/cycle/route.h"

void *cycle_route_arm(uint32_t op)
{
    switch (bitfld_readx(op, 25, 28))
    {
        case 0:
            if (bitfld_readx(op, 4, 25) == 0b10010111111111111000)
                return (NULL); // core_arm_branch_exchange
            // else if (bitfld_readx(op, 4, 25))
            else if (bitfld_readx(op, 22, 25) == 0b000)
                return (NULL); // core_arm_multiply
        case 1:
        default:
            panic(__func__, "Invalid Opcode %u", op);
    }
    return (NULL);
}