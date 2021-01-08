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
 * Run the startcall's of the module's name
 */
void module_start_runmod(char const *name)
{
    struct module *mod;
    
    mod = (struct module *)__start_genesisbackmodules;
    while ((uintptr_t)mod < (uintptr_t)__stop_genesisbackmodules) {
        if (
            !strcmp(mod->name, name) && mod->start &&
            ((!mod->stop && mod->hook == MODULE_HOOK_CORE) || (mod->stop))
        ) {
            if (!mod->initialized) {
                panic("Try to start [%s] uninitialized module", mod->name);
            } else if (mod->running) {
                panic("Try to start [%s] already started module", mod->name);
            } else {
                mod->start();
                mod->running = true;
            }
            break;
        }
        mod++;
    }
}

void module_start_runhook(enum MODULE_HOOKS hook)
{
    struct module *mod;
    
    mod = (struct module *)__start_genesisbackmodules;
    while ((uintptr_t)mod < (uintptr_t)__stop_genesisbackmodules) {
        if (
            mod->hook == hook && mod->start &&
            ((!mod->stop && mod->hook == MODULE_HOOK_CORE) || (mod->stop))
        ) {
             if (mod->initialized && !mod->running) {
                mod->start();
                mod->running = true;
            }
            break;
        }
        mod++;
    }
}
