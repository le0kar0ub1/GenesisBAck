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

void dma1_transfer(void)
{
    struct dmax_iomem *io = (struct dmax_iomem *)mmu_load_addr(DMA_IOMEM_BASE + DMA_IOMEM_ENGINE_SHIFT(1));
    uint32_t sad  = io->sad   & ((1 << 27) - 1);
    uint32_t dad  = io->dad   & ((1 << 27) - 1);
    uint32_t unit = io->count ? io->count & ((1 << 14) - 1) : (1 << 14);

    if (io->ctrl.trns_type) { // word
        unit *= 2;
    } else {
        // all comes good
    }
    while (unit > 0)
    {
        mmu_raw_write16(dad, mmu_read16(sad));
        switch (io->ctrl.dst_ctrl)
        {
            case 0b00: //inc
                dad += 2;
                break;
            case 0b01: // dec
                dad -= 2;
                break;
            // case 0b10: // fix
                // break;
            case 0b11: // Prohibited
                panic("Invalid DMA transfer");
                break;
        }
        switch (io->ctrl.src_ctrl)
        {
            case 0b00: //inc
                sad += 2;
                break;
            case 0b01: // dec
                sad -= 2;
                break;
            // case 0b10: // fix
                // break;
            case 0b11: // Prohibited
                panic("Invalid DMA transfer");
                break;
        }
        unit--;
    }
    /**
     * If the DMA repeat is enabled then don't disable after transfer and loop on
     */
    if (!(io->ctrl.repeat))
        io->ctrl.enable = 0;
}