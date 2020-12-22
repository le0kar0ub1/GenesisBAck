/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "core/cycle/fetch.h"

uint16_t cycle_fetch_thumb(void)
{
    return (mmu_read16(register_read32(PC)));
}

