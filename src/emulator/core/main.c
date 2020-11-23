/******************************************************************************
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include "genesisback.h"
# include "init/initcalls.h"
# include "init/inithooks.h"

int main(void)
{
	return (0);
}

static void nothing(void) {}
REGISTER_BOOTSTRAP_INITCALL(nothing);
REGISTER_CORE_INITCALL(nothing);
REGISTER_POSTCORE_INITCALL(nothing);
REGISTER_SOC_INITCALL(nothing);
REGISTER_LAST_INITCALL(nothing);

REGISTER_BOOTSTRAP_INITHOOK(nothing);
REGISTER_CORE_INITHOOK(nothing);
REGISTER_POSTCORE_INITHOOK(nothing);
REGISTER_SOC_INITHOOK(nothing);
REGISTER_LAST_INITHOOK(nothing);