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
# include <ctype.h>

static void dump_as_char(uint8_t bytes[16])
{
    uint32_t i = 0;
    printf("  |");
    while (i < 16) {
        if (isprint(bytes[i]) == 0) {
            printf(".");
        } else {
            printf("%c", bytes[i]);
        }
        i++;
    }
    printf("|\n");
}

void debug_cmd_dump(int ac, char const **av)
{
    uint32_t size = strtoul(av[1], NULL, get_base(av[1]));
    uint32_t addr = strtoul(av[2], NULL, get_base(av[2]));
    uint8_t bytes[16];
    uint32_t i = 0;

    printf("%08x  ", addr);
    while (i < size) {
        if (i % 16 == 0 && i != 0) {
            dump_as_char(bytes);
            printf("%08x  ", addr + i);
        } else if (i % 8 == 0 && i != 0) {
            printf(" ");
        }
        bytes[i % 16] = mmu_read8(addr + i); 
        printf("%02x ", bytes[i % 16]);
        i++;
    }

    while (i % 16 != 0) {
        if (i % 8 == 0)
            printf(" ");
        bytes[i % 16] = 0;
        printf("00 ");
        i++;
    }
    dump_as_char(bytes);
}