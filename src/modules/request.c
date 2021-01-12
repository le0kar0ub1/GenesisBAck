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

extern struct module __start_genesisbackmodules[];
extern struct module __stop_genesisbackmodules[];

/**
 * Request the module pointer from the name
 */
struct module *module_request_mod(char const *name)
{
    struct module *mod;
    
    mod = (struct module *)__start_genesisbackmodules;
    while ((uintptr_t)mod < (uintptr_t)__stop_genesisbackmodules) {
        if (!strcmp(mod->name, name)) {
            return (mod);
        }
        mod++;
    }
    return (NULL);
}