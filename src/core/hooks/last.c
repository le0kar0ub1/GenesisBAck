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

static void inithook_last(void)
{
}

REGISTER_LAST_INITHOOK(inithook_last);
REGISTER_LAST_INITCALL(inithook_last);

static void exithook_last(void)
{
}

REGISTER_LAST_EXITHOOK(exithook_last);