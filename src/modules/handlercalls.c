/********************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "genesisback.h" 
# include "modules/module.h"
# include <string.h>

extern struct module __start_genesisbackmodules[];
extern struct module __stop_genesisbackmodules[];

/**
 * Run the handlercall's of the module's name
 */
void module_handler_runmod(char const *name)
{
    struct module *mod;
    
    mod = (struct module *)__start_genesisbackmodules;
    while ((uintptr_t)mod < (uintptr_t)__stop_genesisbackmodules) {
        if (!strcmp(mod->name, name) && mod->handler) {
            if (mod->initialized) {
                mod->handler();
            } else {
                panic("Try to run [%s] uninitialized module", mod->name);
            }
            break;
        }
        mod++;
    }
}