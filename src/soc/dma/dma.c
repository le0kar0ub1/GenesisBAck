/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "modules/module.h"
# include "soc/dma.h"

static void dma_init(void)
{
    dma0_init();
    // dma1_init();
    // dma2_init();
    // dma3_init();
}

static void dma_exit(void)
{
    dma0_exit();
    // dma1_exit();
    // dma2_exit();
    // dma3_exit();
}

static void dma_reset(void)
{
    dma_init();
}

REGISTER_MODULE(
    dma,
    "The DMA engine of the GBA",
    MODULE_HOOK_SOC,
    dma_init,
    dma_exit,
    dma_reset,
    NULL,
    NULL
);