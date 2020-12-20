/********************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "init/initcalls.h"

extern initcall_t __start_initcall0[];
extern initcall_t __start_initcall1[];
extern initcall_t __start_initcall2[];
extern initcall_t __start_initcall3[];
extern initcall_t __start_initcall4[];

extern initcall_t __stop_initcall0[];
extern initcall_t __stop_initcall1[];
extern initcall_t __stop_initcall2[];
extern initcall_t __stop_initcall3[];
extern initcall_t __stop_initcall4[];

/*
** Run the given initcall level
*/
void run_initcall_level(u8_t lvl)
{
    initcall_t *hook;
    initcall_t *end;

    switch (lvl) {
        case 0:
            hook = &(*__get_calllevel_start(0));
            end  = &(*__get_calllevel_stop(0));
            break;
        case 1:
            hook = &(*__get_calllevel_start(1));
            end  = &(*__get_calllevel_stop(1));
            break;
        case 2:
            hook = &(*__get_calllevel_start(2));
            end  = &(*__get_calllevel_stop(2));
            break;
        case 3:
            hook = &(*__get_calllevel_start(3));
            end  = &(*__get_calllevel_stop(3));
            break;
        case 4:
            hook = &(*__get_calllevel_start(4));
            end  = &(*__get_calllevel_stop(4));
            break;
        default:
            return;
    }
    while(hook < end && (*hook))
    {
        (*hook)();
        hook++;
    }
}
