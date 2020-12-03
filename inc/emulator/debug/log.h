/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _EMULATOR_DEBUG_LOG_H_
# define _EMULATOR_DEBUG_LOG_H_

# include "def/def.h"
# include <stdio.h>

# define LOG(component, color, ...) printf("[%s%s\x1B[0m]: ", color, #component); printf(__VA_ARGS__)

# define LOG_INF(component, ...) LOG(component, "\x1B[34m", __VA_ARGS__)
# define LOG_WRN(component, ...) LOG(component, "\x1B[33m", __VA_ARGS__)
# define LOG_ERR(component, ...) LOG(component, "\x1B[31m", __VA_ARGS__)

#ifdef VERBOSE_RUN
    # define VERBOSE_LOG(component, ...)  LOG_INF(component, __VA_ARGS__)
#else
    # define VERBOSE_LOG(component, ...)
#endif

#endif /* _EMULATOR_DEBUG_LOG_H_ */