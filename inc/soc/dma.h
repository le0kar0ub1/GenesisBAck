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

# define DMA_IOMEM_BASE         0x40000B0
# define DMA_IOMEM_ENGINE_SIZE  0xC

struct dma_ctrl
{
    union
    {
        struct
        {
            uint16_t _reserved1    : 5;
            uint16_t dst_ctrl      : 2;
            uint16_t src_ctrl      : 2;
            uint16_t repeat        : 1;
            uint16_t trns_type     : 1;
            uint16_t dma3_gamepak  : 1;
            uint16_t start_tim     : 2;
            uint16_t irq           : 1;
            uint16_t enable        : 1;
        };
        uint16_t raw;
    };
};

static_assert(sizeof(struct dma_ctrl) == sizeof(uint16_t));

// struct dma_iomem
// {
//     uint32_t        dma_sad;   /* DMA 0 Source Address */
//     uint32_t        dma_dad;   /* DMA 0 Destination Address */
//     uint16_t        dma_count; /* DMA 0 Word Count */
//     struct dma_ctrl dma_ctrl;  /* DMA 0 Control */
// };

struct dma_iomem
{
    uint32_t        dma0_sad;   /* DMA 0 Source Address */
    uint32_t        dma0_dad;   /* DMA 0 Destination Address */
    uint16_t        dma0_count; /* DMA 0 Word Count */
    struct dma_ctrl dma0_ctrl;  /* DMA 0 Control */
    uint32_t        dma1_sad;   /* DMA 1 Source Address */
    uint32_t        dma1_dad;   /* DMA 1 Destination Address */
    uint16_t        dma1_count; /* DMA 1 Word Count */
    struct dma_ctrl dma1_ctrl;  /* DMA 1 Control */
    uint32_t        dma2_sad;   /* DMA 2 Source Address */
    uint32_t        dma2_dad;   /* DMA 2 Destination Address */
    uint16_t        dma2_count; /* DMA 2 Word Count */
    struct dma_ctrl dma2_ctrl;  /* DMA 2 Control */
    uint32_t        dma3_sad;   /* DMA 3 Source Address */
    uint32_t        dma3_dad;   /* DMA 3 Destination Address */
    uint16_t        dma3_count; /* DMA 3 Word Count */
    struct dma_ctrl dma3_ctrl;  /* DMA 3 Control */
};

void dma0_init(void);
void dma1_init(void);
void dma2_init(void);
void dma3_init(void);

void dma0_exit(void);
void dma1_exit(void);
void dma2_exit(void);
void dma3_exit(void);

void dma0_start(void);
void dma1_start(void);
void dma2_start(void);
void dma3_start(void);

#endif /* _SOC_DMA_H_ */