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
# include <core/core.h>

static struct dmax_iomem internal;
static bool reload;

static void dma_flush_internal(enum DMA_ENGINE engine, struct dmax_iomem *r)
{
    r->sad      = mmu_read32(DMA_IOMEM_GETADDR(3, 0x0));
    r->dad      = mmu_read32(DMA_IOMEM_GETADDR(3, 0x4));
    r->count    = mmu_read16(DMA_IOMEM_GETADDR(3, 0x8));
    r->ctrl.raw = mmu_read16(DMA_IOMEM_GETADDR(3, 0xA));
    r->sad   &= ((1 << 28) - 1);
    r->dad   &= ((1 << 28) - 1);
    r->count &= r->count ? ((1 << 16) - 1) : (1 << 16);
}

static void dma_flush_partial(enum DMA_ENGINE engine, struct dmax_iomem *r)
{
    r->count = mmu_read16(DMA_IOMEM_GETADDR(3, 0x8));
    r->count &= r->count ? ((1 << 16) - 1) : (1 << 16);
    if (r->ctrl.dst_ctrl == 0b11) {
        r->dad = mmu_read32(DMA_IOMEM_GETADDR(3, 0x4)) & ((1 << 28) - 1);
    }
}

void dma3_transfer(void)
{
    if (!reload && mmu_read16(DMA_IOMEM_GETADDR(3, 0xA)) & (1 << 10)) {
        dma_flush_partial(3, &internal);
    } else {
        dma_flush_internal(3, &internal);
    }

    core_cpu_stop_exec();
    while (internal.count > 0)
    {
        if (internal.ctrl.trns_type) {
            mmu_raw_write32(internal.dad, mmu_read32(internal.sad));
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
            case 0b10: break; // fix
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
            case 0b10: break; // fix
             default:
                panic("Invalid DMA transfer");
                break;
        }
        internal.count--;
    }
    core_cpu_restart_exec();

    /**
     * If the DMA repeat is enabled then don't disable after transfer and loop on
     */
    if (!(internal.ctrl.repeat)) {
        mmu_raw_write16(
            DMA_IOMEM_GETADDR(3, 0xA),
            mmu_read16(DMA_IOMEM_GETADDR(3, 0xA)) & ((1 << 15) - 1)
        ); // clear the enabled bit
        reload = true;
    } else {
        reload = false;
    }
}