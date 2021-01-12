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
# include <core/core.h>

static void inithook_core(void)
{
    module_init_runhook(MODULE_HOOK_CORE);
}

REGISTER_CORE_INITHOOK(inithook_core);

static void exithook_core(void)
{
    module_exit_runhook(MODULE_HOOK_CORE);
}

REGISTER_CORE_EXITHOOK(exithook_core);
