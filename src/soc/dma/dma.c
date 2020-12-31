/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "soc/dma.h"

void dma_init(void)
{
    dma0_init();
    // dma1_init();
    // dma2_init();
    // dma3_init();
}

void dma_exit(void)
{
    dma0_exit();
    // dma1_exit();
    // dma2_exit();
    // dma3_exit();
}