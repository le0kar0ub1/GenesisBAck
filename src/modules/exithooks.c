/********************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "modules/exithooks.h"

extern exithook_t __start_exithook0[];
extern exithook_t __start_exithook1[];
extern exithook_t __start_exithook2[];
extern exithook_t __start_exithook3[];

# define __get_exithook_level(type, level) __start_exithook##level

# define EXITHOOK_LEVEL(x)                                  \
    hook = &(*__get_exithook_level(__start_exithook, x));   \
    (*hook)();

/*
** Run all exithooks until CONFIG_INITLEVEL
*/
void exithooks_run_allhooks(void)
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

/**
 * Run the given exit hook
 */
void exithooks_run_hook(enum MODULE_HOOKS hk)
{
    exithook_t *hook;
    switch (hk)
    {
        case MODULE_HOOK_BOOTSTRAP:
            EXITHOOK_LEVEL(0)
            break;
        case MODULE_HOOK_CORE:
            EXITHOOK_LEVEL(1)
            break;
        case MODULE_HOOK_SOC:
            EXITHOOK_LEVEL(2)
            break;
        case MODULE_HOOK_LAST:
            EXITHOOK_LEVEL(3)
            break;
        default:
            break;
    }
}