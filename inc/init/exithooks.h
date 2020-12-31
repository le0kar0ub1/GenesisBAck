/********************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _INIT_EXITHOOKS_H_
# define _INIT_EXITHOOKS_H_

typedef void (*exithook_t)(void);

enum exithooks {
    EXITHOOK_BOOTSTRAP = 0,
    EXITHOOK_CORE = 1,
    EXITHOOK_SOC = 2,
    EXITHOOK_LAST = 3,
    EXITHOOK_MAX = 3
};

# define __define_exithook(level, fn, id) \
    static const exithook_t __exithook_##fn##id \
    __attribute__((__used__, __section__("exithook" level))) = fn

# define __get_exithook_level(type, level) __start_exithook##level

# define REGISTER_BOOTSTRAP_EXITHOOK(fn)  __define_exithook("0", fn, 0)
# define REGISTER_CORE_EXITHOOK(fn)       __define_exithook("1", fn, 1)
# define REGISTER_SOC_EXITHOOK(fn)        __define_exithook("2", fn, 2)
# define REGISTER_LAST_EXITHOOK(fn)       __define_exithook("3", fn, 3)

void run_exithooks_bylevel(void);

#endif /* !_INIT_EXITHOOKS_H_ */
