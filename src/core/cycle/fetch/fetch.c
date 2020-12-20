/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "machine/gba/cpu/cycle/fetch.h"

/**
 * TODO: Achieve this part with the memory management and ADD a translation to ALL pointers 
 */

uint32_t cpu_fetch_instr32(void)
{
    uint32_t *fetch = (uint32_t *)(uint64_t)(fetch_register_base32(PC));
    return (*fetch);
}

uint16_t cpu_fetch_instr16(void)
{
    uint16_t *fetch = (uint16_t *)(uint64_t)(fetch_register_base32(PC));
    return (*fetch);
}

