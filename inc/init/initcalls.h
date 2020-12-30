/********************************************************************************
**
**  This file is part of the Genesisback project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _INIT_INITCALLS_H_
# define _INIT_INITCALLS_H_

# include "def/def.h"

typedef void (*initcall_t)(void);

# define __define_initcall(level, fn, id)                                       \
    static const initcall_t __initcall_##fn##id                                 \
    __attribute__((__used__, __section__("initcall" level))) = fn

# define __get_calllevel_start(level) (__start_initcall##level)
# define __get_calllevel_stop(level) (__stop_initcall##level)

# define REGISTER_BOOTSTRAP_INITCALL(fn)  __define_initcall("0", fn, 0)
# define REGISTER_CORE_INITCALL(fn)       __define_initcall("1", fn, 1)
# define REGISTER_SOC_INITCALL(fn)        __define_initcall("2", fn, 2)
# define REGISTER_LAST_INITCALL(fn)       __define_initcall("3", fn, 3)

void run_initcalls(void);
void run_initcall_level(u8_t);

# define run_boot_initcalls()       run_initcall_level(0)
# define run_core_initcalls()       run_initcall_level(1)
# define run_soc_initcalls()        run_initcall_level(2)
# define run_last_initcalls()       run_initcall_level(3)

#endif /* !_INIT_INITCALLS_H_ */
