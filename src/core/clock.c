/******************************************************************************
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include <core/core.h>

# pragma message "Implement me"

static size_t cycle;

void core_inc_clock(size_t inc)
{
    cycle += inc;
}

size_t core_get_clock(void)
{
    return (cycle);
}