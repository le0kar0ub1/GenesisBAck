/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _IO_PORTS_H_
# define _IO_PORTS_H_

# include "def/def.h"

/*
** A defined port
*/
struct io_port {
    char const *name;
    ushort port;
};

# define REGISTER_IO_PORT(pname, vport)                                 \
    __aligned(sizeof(void *)) __used __section(".genesisback_io_port")  \
    static struct io_port pname = {                   	  		        \
        .name = #pname,                                                 \
        .port = vport                                                   \
    }

#endif /* !_IO_PORTS_H_ */