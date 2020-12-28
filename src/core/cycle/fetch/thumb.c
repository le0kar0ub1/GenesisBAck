/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "core/cycle/fetch.h"

uint16_t core_fetch_thumb(void)
{
    uint32_t addr = register_read32(PC);
    FETCH_RETURN (mmu_read16(addr), addr);
}

