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
# include <core/exceptions.h>
# include <gba/interrupt.h>

static struct dmax_iomem internal;
static bool reload = true;

static void dma_flush_internal(void)
{
    internal.sad      = mmu_read32(DMA_IOMEM_GETADDR(2, 0x0));
    internal.dad      = mmu_read32(DMA_IOMEM_GETADDR(2, 0x4));
    internal.count    = mmu_read16(DMA_IOMEM_GETADDR(2, 0x8));
    internal.ctrl.raw = mmu_read16(DMA_IOMEM_GETADDR(2, 0xA));
    internal.sad   &= ((1 << 27) - 1);
    internal.dad   &= ((1 << 27) - 1);
    internal.count &= internal.count ? ((1 << 14) - 1) : (1 << 14);
}

static void dma_flush_partial(void)
{
    internal.count = mmu_read16(DMA_IOMEM_GETADDR(2, 0x8));
    internal.count &= internal.count ? ((1 << 14) - 1) : (1 << 14);
    if (internal.ctrl.dst_ctrl == 0b11) {
        internal.dad = mmu_read32(DMA_IOMEM_GETADDR(2, 0x4)) & ((1 << 27) - 1);
    }
}

static bool dma_timing_check(void)
{
    uint32_t dad;

    switch ((mmu_read16(DMA_IOMEM_GETADDR(2, 0xA)) >> 12) & 0b11)
    {
        case 0b00: // immediate
            return (true);
        case 0b01: // V-Blank
            if (mmu_read16(0x4000004) & 0b1)
                return (true);
            return (false);
        case 0b10: // H-Blank
            if ((mmu_read16(0x4000004) >> 1) & 0b1)
                return (true);
            return (false);
        case 0b11: // Special : Sound FIFO
            return (false);
            dad = mmu_read32(DMA_IOMEM_GETADDR(2, 0x4));
            if (dad != 0x40000A0 && dad != 0x40000A4) {
                panic("DMA 2 has dest dad %#x in Sound FIFO", dad);
            }
            return (true);
    }
    return (false);
}


static void dma_handle_special_timing(void)
{
    internal.count = 0x4;
    internal.ctrl.trns_type = DMA_TRNSTYPE_CTRL_WORD;
    internal.ctrl.dst_ctrl = DMA_ADDR_CTRL_FIX;
}

void dma2_transfer(void)
{
    if (!dma_timing_check())
        return;

    if (!reload && mmu_read16(DMA_IOMEM_GETADDR(2, 0xA)) & (1 << 9)) {
        dma_flush_partial();
    } else {
        dma_flush_internal();
    }

    if (((mmu_read16(DMA_IOMEM_GETADDR(1, 0xA)) >> 12) & 0b11) == 0b11) {
        dma_handle_special_timing();
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
            DMA_IOMEM_GETADDR(2, 0xA),
            mmu_read16(DMA_IOMEM_GETADDR(2, 0xA)) & ((1 << 15) - 1)
        ); // clear the enabled bit
        reload = true;
        if ((bool)(mmu_read16(DMA_IOMEM_GETADDR(2, 0xA)) & (1 << 14))) { // is IRQ enabled ?
            interrupt_raise_irq(IRQ_DMA2);
        }
    } else {
        reload = false;
    }
}