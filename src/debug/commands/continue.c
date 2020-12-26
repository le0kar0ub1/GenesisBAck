/******************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include "debug/debug.h"
# include "core/core.h"

void debug_cmd_continue(int ac, char const **av)
{
    while (1) {
    #if DEBUG_STATE_MASTER
        debug_cmd_burst(1, NULL);
    #endif
        core_scheduler();
    }
}