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

extern struct module __start_genesisbackmodules[];
extern struct module __stop_genesisbackmodules[];

static void debug_cmd_module_list(void)
{
    struct module *mod;
    
    mod = (struct module *)__start_genesisbackmodules;
    while ((uintptr_t)mod < (uintptr_t)__stop_genesisbackmodules) {
        printf(
            "[%s] %s hook %u: %s\n",
            mod->name,
            mod->initialized ? "initialized" : "uninitialized",
            mod->hook,
            mod->desc
        );
        mod++;
    }
}

void debug_cmd_module(int ac, char const **av)
{
    struct module *mod;
    
    if (ac == 2) {
        if (!strcmp(av[1], "list")) {
            debug_cmd_module_list();
        } else {
            module_info_runmod(av[1]);
        }
    }
}