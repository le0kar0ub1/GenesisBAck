/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "core/cycle/fetch.h"

uint32_t core_fetch_arm(void)
{
    FETCH_RETURN (mmu_read32(register_read32(PC)));
}