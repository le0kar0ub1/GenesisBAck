/********************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _INIT_INITHOOKS_H_
# define _INIT_INITHOOKS_H_

typedef void (*inithook_t)(void);

enum inithooks {
    INITHOOK_BOOTSTRAP = 0,
    INITHOOK_CORE = 1,
    INITHOOK_SOC = 2,
    INITHOOK_LAST = 3,
    INITHOOK_MAX = 3
};

# define __define_inithook(level, fn, id) \
    static const inithook_t __inithook_##fn##id \
    __attribute__((__used__, __section__("inithook" level))) = fn

# define __get_hooklevel(type, level) __start_inithook##level

# define REGISTER_BOOTSTRAP_INITHOOK(fn)  __define_inithook("0", fn, 0)
# define REGISTER_CORE_INITHOOK(fn)       __define_inithook("1", fn, 1)
# define REGISTER_SOC_INITHOOK(fn)        __define_inithook("2", fn, 2)
# define REGISTER_LAST_INITHOOK(fn)       __define_inithook("3", fn, 3)

void run_inithooks_bylevel(void);

#endif /* !_INIT_INITHOOKS_H_ */
