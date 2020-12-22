/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _IO_LOG_H_
# define _IO_LOG_H_

# include "def/def.h"
# include <stdio.h>

# define LOG(component, color, ...) printf("[%s%s\x1B[0m]: ", color, #component); printf(__VA_ARGS__)

# define LOG_INF(component, ...) LOG(component, "\x1B[34m", __VA_ARGS__)
# define LOG_WRN(component, ...) LOG(component, "\x1B[33m", __VA_ARGS__)
# define LOG_ERR(component, ...) LOG(component, "\x1B[31m", __VA_ARGS__)

#ifdef VERBOSE_RUN
    # define LOG_VERBOSE(component, ...) LOG_INF(component, __VA_ARGS__)
#else
    # define LOG_VERBOSE(component, ...)
#endif

#ifdef DEBUG_STATE_MASTER
    # define LOG_DEBUG(component, ...) LOG_INF(component, __VA_ARGS__)
#else
    # define LOG_DEBUG(component, ...)
#endif

#endif /* _IO_LOG_H_ */