/******************************************************************************
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include  "core/core.h"

uint32_t core_read_state(void)
{
    return (register_read_cpsr().state);
}

uint32_t core_read_opmode(void)
{
    return (register_read_cpsr().opmode);
}