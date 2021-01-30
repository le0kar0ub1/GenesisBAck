/********************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <genesisback.h>
# include <modules/module.h>
# include <string.h>

extern struct module __start_genesisback_modules[];
extern struct module __stop_genesisback_modules[];

static void module_reset_fromhook(enum MODULE_HOOKS hook)
{
    struct module *mod;

newhook:
    mod = (struct module *)__start_genesisback_modules;
    while ((uintptr_t)mod < (uintptr_t)__stop_genesisback_modules) {
        if (mod->hook == hook && mod->reset) {
            if (!mod->initialized) {
                panic("Try to reset [%s] uninitialized module", mod->name);
            } else {
                mod->reset();
            }
        }
        mod++;
    }
    if (hook < MODULE_HOOK_MAX) {
        hook++;
        goto newhook;
    }
}

/**
 * Run the resetcall's of the module's name and all the uppers one's
 */
void module_reset_runmod(char const *name)
{
    struct module *mod;
    
    mod = (struct module *)__start_genesisback_modules;
    while ((uintptr_t)mod < (uintptr_t)__stop_genesisback_modules) {
        if (!strcmp(mod->name, name) && mod->reset && mod->initialized) {
            mod->reset();
            if (mod->hook < MODULE_HOOK_MAX)
                module_reset_fromhook(mod->hook + 1);
            break;
        }
        mod++;
    }
}

/*
** Run the given resetcall level and all the uppers one's
*/
void module_reset_runhook(enum MODULE_HOOKS hook)
{
    module_reset_fromhook(hook);
}