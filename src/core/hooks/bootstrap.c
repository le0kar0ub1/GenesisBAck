/********************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "init/inithooks.h"
# include "init/exithooks.h"
# include "init/initcalls.h"
# include "mmu/mmu.h"
# include "core/core.h"
# include <stdlib.h>

extern char const *rom;

static void inithook_bootstrap(void)
{
    LOG_VERBOSE("Welcome to GenesisBack");
    if (!mmu_init())
        panic("MMU init failed");
    if (!mmu_load_rom(rom))
        panic("Load rom failed");
}

REGISTER_BOOTSTRAP_INITHOOK(inithook_bootstrap);
REGISTER_BOOTSTRAP_INITCALL(inithook_bootstrap);

static void exithook_bootstrap(void)
{
    mmu_exit();
}

REGISTER_BOOTSTRAP_EXITHOOK(exithook_bootstrap);