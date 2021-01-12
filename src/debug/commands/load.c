/******************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include <debug/debug.h>
# include <mmu/mmu.h>
# include <stdlib.h>
# include <string.h>

void debug_cmd_load(int ac, char const **av)
{
    uint32_t size;
    uint32_t addr;

    if (ac == 2) {
        size = 4;
        addr = strtoul(av[1], NULL, get_base(av[1]));
    } else if (ac == 3) {
        size = strtoul(av[1], NULL, get_base(av[1]));
        addr = strtoul(av[2], NULL, get_base(av[2]));
    }

    switch (size) {
        case 1:
            printf("%02x\n", mmu_read8(addr));
            break;
        case 2:
            printf("%04x\n", mmu_read16(addr));
            break;
        case 4:
            printf("%08x\n", mmu_read32(addr));
            break;
        default:
            break;
    }
}