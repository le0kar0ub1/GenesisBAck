/********************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "modules/inithooks.h"
# include "modules/exithooks.h"
# include "modules/module.h"
# include "mmu/mmu.h"
# include "core/core.h"

extern char const *rom;

static void inithook_bootstrap(void)
{
    module_init_runhook(MODULE_HOOK_BOOTSTRAP);
    if (!mmu_load_rom(rom))
        panic("ROM load failed");
}

REGISTER_BOOTSTRAP_INITHOOK(inithook_bootstrap);

static void exithook_bootstrap(void)
{
    module_exit_runhook(MODULE_HOOK_BOOTSTRAP);
}

REGISTER_BOOTSTRAP_EXITHOOK(exithook_bootstrap);