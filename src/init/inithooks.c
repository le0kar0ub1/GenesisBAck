/********************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "init/inithooks.h"

extern inithook_t __start_inithook0[];
extern inithook_t __start_inithook1[];
extern inithook_t __start_inithook2[];
extern inithook_t __start_inithook3[];
extern inithook_t __start_inithook4[];

# define INITHOOK_LEVEL(x)                      \
    hook = &(*__get_hooklevel(__start_inithook, x));   \
    (*hook)();

#ifndef CONFIG_INITLEVEL
    # define CONFIG_INITLEVEL INITHOOK_MAX
#endif

/*
** Run all inithooks until CONFIG_INITLEVEL
*/
void run_inithooks_bylevel(void)
{
    inithook_t *hook;
#if CONFIG_INITLEVEL >= 0
    INITHOOK_LEVEL(0)
#endif
#if CONFIG_INITLEVEL >= 1
    INITHOOK_LEVEL(1)
#endif
#if CONFIG_INITLEVEL >= 2
    INITHOOK_LEVEL(2)
#endif
#if CONFIG_INITLEVEL >= 3
    INITHOOK_LEVEL(3)
#endif
#if CONFIG_INITLEVEL >= 4
    INITHOOK_LEVEL(4)
#endif
}