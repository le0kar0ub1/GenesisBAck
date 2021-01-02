/******************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include "debug/debug.h"
# include "modules/module.h"
# include <string.h>

extern struct module __start_genesisbackmodule[];
extern struct module __stop_genesisbackmodule[];

void debug_cmd_module(int ac, char const **av)
{
    struct module *mod;
    
    if (ac == 2) {
        mod = (struct module *)__start_genesisbackmodule;
        while ((uintptr_t)mod < (uintptr_t)__stop_genesisbackmodule) {
            if (!strcmp(mod->name, av[1])) {
                mod->info();
                break;
            }
            mod++;
        }
    }
}