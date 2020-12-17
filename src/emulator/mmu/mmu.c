/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "emulator/mmu/mmu.h"
# include <stdlib.h>

hostaddr_t base;

static void init_mmu(void)
{
    /* Big dirty static 32k alloc */
    base = malloc(32000000);
}

hostaddr_t trns_to_host(virtaddr_t virt)
{
    return ((hostaddr_t)ADD_PTR(base, virt));
}

virtaddr_t trns_to_virt(hostaddr_t host)
{
    return ((virtaddr_t)SUB_PTR(host, base));
}