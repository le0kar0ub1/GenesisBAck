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

static void inithook_bootstrap(void)
{

}

REGISTER_BOOTSTRAP_INITHOOK(inithook_bootstrap);
REGISTER_BOOTSTRAP_INITCALL(inithook_bootstrap);