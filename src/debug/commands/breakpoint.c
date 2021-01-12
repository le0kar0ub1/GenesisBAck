/******************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include <debug/debug.h>
# include <string.h>

static int32_t breakpoint = -1;

void debug_cmd_breakpoint(int ac, char const **av)
{
    breakpoint = strtol(av[1], NULL, get_base(av[1]));
}

int32_t breakpoint_get_and_remove(void)
{
    int32_t brk = breakpoint;
    breakpoint = -1;
    return (brk);
}