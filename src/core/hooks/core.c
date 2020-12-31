/********************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "init/inithooks.h"
# include "init/initcalls.h"
# include "init/exithooks.h"
# include "core/core.h"

static void inithook_core(void)
{
    LOG_VERBOSE("Initializing core");
	core_init();
}

REGISTER_CORE_INITHOOK(inithook_core);
REGISTER_CORE_INITCALL(inithook_core);

static void exithook_core(void)
{
    core_exit();
}

REGISTER_CORE_EXITHOOK(exithook_core);