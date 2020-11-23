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

static void inithook_soc(void)
{

}

REGISTER_SOC_INITHOOK(inithook_soc);
REGISTER_SOC_INITCALL(inithook_soc);