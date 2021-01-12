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

static void inithook_last(void)
{
    module_init_runhook(MODULE_HOOK_LAST);
}

REGISTER_LAST_INITHOOK(inithook_last);

static void exithook_last(void)
{
    module_exit_runhook(MODULE_HOOK_LAST);
}

REGISTER_LAST_EXITHOOK(exithook_last);