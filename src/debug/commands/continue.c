/******************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include <debug/debug.h>
# include <core/core.h>

void debug_cmd_continue(int ac, char const **av)
{
    int32_t brk = breakpoint_get_and_remove();

    while (1) {
        if (
            brk != -1 && 
            register_read32(PC) == (uint32_t)brk + (core_read_state() == STATE_ARM ? 4 : 2)
        )
            break;
    #if DEBUG_STATE_MASTER
        debug_cmd_burst(1, NULL);
    #endif
        core_scheduler();
    }
}