/********************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "init/exithooks.h"

extern exithook_t __start_exithook0[];
extern exithook_t __start_exithook1[];
extern exithook_t __start_exithook2[];
extern exithook_t __start_exithook3[];

# define EXITHOOK_LEVEL(x)                                  \
    hook = &(*__get_exithook_level(__start_exithook, x));   \
    (*hook)();

#ifndef CONFIG_INITLEVEL
    # define CONFIG_INITLEVEL EXITHOOK_MAX
#endif

/*
** Run all exithooks until CONFIG_INITLEVEL
*/
void run_exithooks_bylevel(void)
{
    exithook_t *hook;
#if CONFIG_INITLEVEL >= 3
    EXITHOOK_LEVEL(3)
#endif
#if CONFIG_INITLEVEL >= 2
    EXITHOOK_LEVEL(2)
#endif
#if CONFIG_INITLEVEL >= 1
    EXITHOOK_LEVEL(1)
#endif
#if CONFIG_INITLEVEL >= 0
    EXITHOOK_LEVEL(0)
#endif
}