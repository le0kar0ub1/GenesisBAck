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

/**
 * Request the module pointer from the name
 */
struct module *module_request_mod(char const *name)
{
    struct module *mod;
    
    mod = (struct module *)__start_genesisback_modules;
    while ((uintptr_t)mod < (uintptr_t)__stop_genesisback_modules) {
        if (!strcmp(mod->name, name)) {
            return (mod);
        }
        mod++;
    }
    return (NULL);
}