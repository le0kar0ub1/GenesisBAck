/********************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "modules/module.h"
# include <string.h>

extern struct module __start_genesisbackmodule[];
extern struct module __stop_genesisbackmodule[];

/**
 * Run the resetcall's of the module's name
 */
void module_reset_runmod(char const *name)
{
    struct module *mod;
    
    mod = (struct module *)__start_genesisbackmodule;
    while ((uintptr_t)mod < (uintptr_t)__stop_genesisbackmodule) {
        if (!strcmp(mod->name, name) && mod->reset) {
            mod->reset();
            break;
        }
        mod++;
    }
}

/*
** Run the given resetcall level
*/
void module_reset_runhook(enum MODULE_HOOKS hook)
{
    struct module *mod;
    
    mod = (struct module *)__start_genesisbackmodule;
    while ((uintptr_t)mod < (uintptr_t)__stop_genesisbackmodule) {
        if (mod->hook == hook && mod->reset) {
            mod->reset();
            break;
        }
        mod++;
    }
}