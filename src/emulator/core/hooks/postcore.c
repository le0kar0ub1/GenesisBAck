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

static void inithook_postcore(void)
{

}

REGISTER_POSTCORE_INITHOOK(inithook_postcore);
REGISTER_POSTCORE_INITCALL(inithook_postcore);