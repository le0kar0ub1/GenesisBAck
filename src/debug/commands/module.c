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

void debug_cmd_module(int ac, char const **av)
{
    struct module *mod;
    
    if (ac == 2) {
        module_info_runmod(av[1]);
    }
}