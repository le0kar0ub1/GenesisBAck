/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "soc/system.h"
# include "modules/module.h"
# include "mmu/mmu.h"

struct system_iomem *io = NULL;

static void system_init(void)
{
    io = (struct system_iomem *)mmu_load_addr(SYSTEM_IOMEM_BASE);
}

static void system_exit(void)
{
    io = NULL;
}

static void system_reset(void)
{
    system_init();
}

REGISTER_MODULE(
    system,
    "The system control regs of the GBA",
    MODULE_HOOK_SOC,
    system_init,
    system_exit,
    system_reset,
    NULL,
    NULL
);