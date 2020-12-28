/******************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include "debug/debug.h"
# include "string.h"

static uint32_t breakpoint = 0x0;

void debug_cmd_breakpoint(int ac, char const **av)
{
    breakpoint = strtoul(av[1], NULL, get_base(av[1]));
}

uint32_t breakpoint_get_and_remove(void)
{
    uint32_t brk = breakpoint;
    breakpoint = 0x0;
    return (brk);
}