/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <mmu/mmu.h>
# include <gba/dma.h>

static struct dmax_iomem internal;
static bool reload;

void dma0_transfer(void)
{
    dma_flush_internal(0, &internal);

    while (internal.count > 0)
    {
        if (internal.ctrl.trns_type) {
            mmu_raw_write32(internal.dad, mmu_read16(internal.sad));
        } else {
            mmu_raw_write16(internal.dad, mmu_read16(internal.sad));
        }
        switch (internal.ctrl.dst_ctrl)
        {
            case 0b00: //inc
                internal.dad += internal.ctrl.trns_type ? 4 : 2;
                break;
            case 0b01: // dec
                internal.dad -= internal.ctrl.trns_type ? 4 : 2;
                break;
            case 0b11: // inc/reload
                internal.dad += internal.ctrl.trns_type ? 4 : 2;
                break;
            default:
                panic("Invalid DMA transfer");
                break;
        }
        switch (internal.ctrl.src_ctrl)
        {
            case 0b00: //inc
                internal.sad += internal.ctrl.trns_type ? 4 : 2;
                break;
            case 0b01: // dec
                internal.sad -= internal.ctrl.trns_type ? 4 : 2;
                break;
             default:
                panic("Invalid DMA transfer");
                break;
        }
        internal.count--;
    }
    /**
     * If the DMA repeat is enabled then don't disable after transfer and loop on
     */
    if (!(internal.ctrl.repeat)) {
        internal.ctrl.enable = 0;
        mmu_raw_write16(
            DMA_IOMEM_BASE + DMA_IOMEM_ENGINE_SHIFT(0) + 0xA,
            mmu_read16(DMA_IOMEM_BASE + DMA_IOMEM_ENGINE_SHIFT(0) + 0xA) | (1 << 15)
        );
        reload = true;
    } else {
        reload = false;
    }
}