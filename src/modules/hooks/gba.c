/********************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <modules/inithooks.h>
# include <modules/exithooks.h>
# include <modules/module.h>

static void inithook_gba(void)
{
    module_init_runhook(MODULE_HOOK_GBA);
    module_start_runhook(MODULE_HOOK_GBA);
}

REGISTER_GBA_INITHOOK(inithook_gba);

static void exithook_gba(void)
{
    module_stop_runhook(MODULE_HOOK_GBA);
    module_exit_runhook(MODULE_HOOK_GBA);
}

REGISTER_GBA_EXITHOOK(exithook_gba);