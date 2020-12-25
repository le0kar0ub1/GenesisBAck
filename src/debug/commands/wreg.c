/******************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include "debug/debug.h"
# include "core/core.h"
# include <stdlib.h>
# include <string.h>

void debug_cmd_wreg(int ac, char const **av)
{
    int32_t reg = get_reg(av[1]);
    int32_t val = strtol(av[2], NULL, get_base(av[2]));

    if (reg >= 0 && reg <= 15)
        register_write32(reg, val);
}