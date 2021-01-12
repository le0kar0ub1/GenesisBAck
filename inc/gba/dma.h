/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _GBA_DMA_H_
# define _GBA_DMA_H_

# include <genesisback.h>

enum DMA_ENGINE {
    DMA_ENGINE0 = 0,
    DMA_ENGINE1 = 1,
    DMA_ENGINE2 = 2,
    DMA_ENGINE3 = 3
};

# define DMA_IOMEM_BASE            0x40000B0
# define DMA_IOMEM_ENGINE_SHIFT(x) (x * 0xC)

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

struct dmax_iomem
{
    uint32_t        dma_sad;   /* DMA 0 Source Address */
    uint32_t        dma_dad;   /* DMA 0 Destination Address */
    uint16_t        dma_count; /* DMA 0 Word Count */
    struct dma_ctrl dma_ctrl;  /* DMA 0 Control */
};

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

struct dmax_iomem *dma_get_engine_io(enum DMA_ENGINE engine);

void dma0_transfer(void);
void dma1_transfer(void);
void dma2_transfer(void);
void dma3_transfer(void);

#endif /* _GBA_DMA_H_ */