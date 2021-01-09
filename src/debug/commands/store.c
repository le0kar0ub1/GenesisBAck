/******************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include "debug/debug.h"
# include "mmu/mmu.h"
# include <stdlib.h>
# include <string.h>

void debug_cmd_store(int ac, char const **av)
{
    uint32_t size;
    uint32_t addr;
    uint32_t expr;

    if (ac == 3) {
        size = 4;
        expr = strtoul(av[1], NULL, get_base(av[1]));
        addr = strtoul(av[2], NULL, get_base(av[2]));
    } else if (ac == 4) {
        size = strtoul(av[1], NULL, get_base(av[1]));
        expr = strtoul(av[2], NULL, get_base(av[2]));
        addr = strtoul(av[3], NULL, get_base(av[3]));
    }

    switch (size) {
        case 1:
            mmu_write8(addr,  (uint8_t)expr);
            break;
        case 2:
            mmu_write16(addr, (uint16_t)expr);
            break;
        case 4:
            mmu_write32(addr, (uint32_t)expr);
            break;
        default:
            break;
    }
}