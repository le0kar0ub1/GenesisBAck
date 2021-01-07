/********************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _MODULES_EXITHOOKS_H_
# define _MODULES_EXITHOOKS_H_

# include "modules/module.h"

typedef void (*exithook_t)(void);

# define __define_exithook(level, fn, id) \
    static const exithook_t __exithook_##fn##id \
    __attribute__((__used__, __section__("exithook" level))) = fn

# define REGISTER_BOOTSTRAP_EXITHOOK(fn)  __define_exithook("0", fn, 0)
# define REGISTER_CORE_EXITHOOK(fn)       __define_exithook("1", fn, 1)
# define REGISTER_GBA_EXITHOOK(fn)        __define_exithook("2", fn, 2)
# define REGISTER_LAST_EXITHOOK(fn)       __define_exithook("3", fn, 3)

void exithooks_run_allhooks(void);
void exithooks_run_hook(enum MODULE_HOOKS hook);

#endif /* !_MODULES_EXITHOOKS_H_ */
