/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _EMULATOR_LOG_H_
# define _EMULATOR_LOG_H_

# include <def/def.h>
# include <stdio.h>

# define LOG(color, ...) printf("[%s%s\x1B[0m]: ", color, __func__); printf(__VA_ARGS__); printf("\n");

# define LOG_INF(...) LOG("\x1B[34m", __VA_ARGS__)
# define LOG_WRN(...) LOG("\x1B[33m", __VA_ARGS__)
# define LOG_ERR(...) LOG("\x1B[31m", __VA_ARGS__)

#if VERBOSE_RUN == true
    # define LOG_VERBOSE(...) LOG_INF(__VA_ARGS__)
#else
    # define LOG_VERBOSE(...)
#endif

#if DEBUG_STATE_MASTER == true
    # define LOG_DEBUG(...) LOG_INF(__VA_ARGS__)
#else
    # define LOG_DEBUG(...)
#endif

#endif /* _EMULATOR_LOG_H_ */