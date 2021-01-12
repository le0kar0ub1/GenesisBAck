/********************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _MODULES_INITHOOKS_H_
# define _MODULES_INITHOOKS_H_

# include <modules/module.h>

typedef void (*inithook_t)(void);

# define __define_inithook(level, fn, id) \
    static const inithook_t __inithook_##fn##id \
    __attribute__((__used__, __section__("inithook" level))) = fn

# define REGISTER_BOOTSTRAP_INITHOOK(fn)  __define_inithook("0", fn, 0)
# define REGISTER_CORE_INITHOOK(fn)       __define_inithook("1", fn, 1)
# define REGISTER_GBA_INITHOOK(fn)        __define_inithook("2", fn, 2)
# define REGISTER_LAST_INITHOOK(fn)       __define_inithook("3", fn, 3)

void inithooks_run_allhooks(void);
void inithooks_run_hook(enum MODULE_HOOKS hook);

#endif /* !_MODULES_INITHOOKS_H_ */
