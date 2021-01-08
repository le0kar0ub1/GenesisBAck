/********************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "modules/inithooks.h"

extern inithook_t __start_inithook0[];
extern inithook_t __start_inithook1[];
extern inithook_t __start_inithook2[];
extern inithook_t __start_inithook3[];

# define __get_inithook_level(type, level) __start_inithook##level

# define INITHOOK_LEVEL(x)                      \
    hook = &(*__get_inithook_level(__start_inithook, x));   \
    (*hook)();

/*
** Run all inithooks until CONFIG_INITLEVEL
*/
void inithooks_run_allhooks(void)
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
}

/**
 * Run the given init hook
 */
void inithooks_run_hook(enum MODULE_HOOKS hk)
{
    inithook_t *hook;
    switch (hk)
    {
        case MODULE_HOOK_BOOTSTRAP:
            INITHOOK_LEVEL(0);
            break;
        case MODULE_HOOK_CORE:
            INITHOOK_LEVEL(1);
            break;
        case MODULE_HOOK_GBA:
            INITHOOK_LEVEL(2);
            break;
        case MODULE_HOOK_LAST:
            INITHOOK_LEVEL(3);
            break;
        default:
            break;
    }
}