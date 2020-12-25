/******************************************************************************
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include "debug/debug.h"

extern const struct command commands[];

void debug_cmd_help(int ac, char const **av)
{
    if (ac == 2) {
        int idx = get_command_descriptor_index(av[1]);
        if (idx >= 0)
            printf("    %s: %s\n", commands[idx].name, commands[idx].description);
    } else if (ac == 1) {
        for (uint32_t i = 0; commands[i].name; i++)
            printf("    %s: %s\n", commands[i].name, commands[i].description);
    }
}