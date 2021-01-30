/********************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <modules/module.h>
# include <string.h>

extern struct module __start_genesisback_modules[];
extern struct module __stop_genesisback_modules[];

/**
 * Run the initcall's of the module's name
 */
void module_init_runmod(char const *name)
{
    struct module *mod;
    
    mod = (struct module *)__start_genesisback_modules;
    while ((uintptr_t)mod < (uintptr_t)__stop_genesisback_modules) {
        if (!strcmp(mod->name, name) && mod->init) {
            mod->init();
            mod->initialized = true;
            break;
        }
        mod++;
    }
}

/*
** Run the given initcall level
*/
void module_init_runhook(enum MODULE_HOOKS hook)
{
    struct module *mod;
    
    mod = (struct module *)__start_genesisback_modules;
    while ((uintptr_t)mod < (uintptr_t)__stop_genesisback_modules) {
        if (mod->hook == hook && mod->init) {
            mod->init();
            mod->initialized = true;
        }
        mod++;
    }
}