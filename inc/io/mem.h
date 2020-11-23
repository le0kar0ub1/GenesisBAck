/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _IO_MEM_H_
# define _IO_MEM_H_

# include "def/def.h"
# include "def/access.h"

/*
** A memory area
*/
struct memory_area
{
    char const    *name;
    uintptr_t     start;
    uintptr_t     end;
    access_flag_t flag;
};

# define REGISTER_IO_MEM(mname, mstart, mend, mflag)                     \
    __aligned(sizeof(void *)) __used __section("genesisback_io_mem")     \
    static const struct memory_area mname = {                            \
        .name  = #mname,                                                 \
        .start = mstart,                                                 \
        .end   = mend,                                                   \
        .flag  = mflag                                                   \
    };

#endif /* !_IO_PORTS_H */