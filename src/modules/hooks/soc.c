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

static void inithook_soc(void)
{
}

REGISTER_SOC_INITHOOK(inithook_soc);

static void exithook_soc(void)
{
}

REGISTER_SOC_EXITHOOK(exithook_soc);