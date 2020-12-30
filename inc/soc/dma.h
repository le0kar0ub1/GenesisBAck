/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _SOC_DMA_H_
# define _SOC_DMA_H_

# include "genesisback.h"

# define DMA_IOMEM_BASE 0x40000B0

struct dma_iomem
{
    uint32_t  dma0_sad;   /* DMA 0 Source Address */
    uint32_t  dma0_dad;   /* DMA 0 Destination Address */
    uint16_t  dma0_count; /* DMA 0 Word Count */
    uint16_t  dma0_ctl; /* DMA 0 Control */
    uint32_t  dma1_sad;   /* DMA 1 Source Address */
    uint32_t  dma1_dad;   /* DMA 1 Destination Address */
    uint16_t  dma1_count; /* DMA 1 Word Count */
    uint16_t  dma1_ctl; /* DMA 1 Control */
    uint32_t  dma2_sad;   /* DMA 2 Source Address */
    uint32_t  dma2_dad;   /* DMA 2 Destination Address */
    uint16_t  dma2_count; /* DMA 2 Word Count */
    uint16_t  dma2_ctl; /* DMA 2 Control */
    uint32_t  dma3_sad;   /* DMA 3 Source Address */
    uint32_t  dma3_dad;   /* DMA 3 Destination Address */
    uint16_t  dma3_count; /* DMA 3 Word Count */
    uint16_t  dma3_ctl; /* DMA 3 Control */
};

#endif /* _SOC_DMA_H_ */