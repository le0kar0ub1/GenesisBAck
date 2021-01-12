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

void dma0_transfer(void)
{
    struct dmax_iomem *io = dma_get_engine_io(0);
    uint32_t sad;
    uint32_t dad;
    uint32_t unit;

    mmu_safe_expr(sad = io->dma_sad);
    mmu_safe_expr(dad = io->dma_dad);
    mmu_safe_expr(unit = io->dma_count);
    
    sad &= ((1 << 27) - 1);
    dad &= ((1 << 27) - 1);
    unit = unit ? unit & ((1 << 14) - 1) : (1 << 14);

    if (io->dma_ctrl.trns_type) { // word
        unit *= 2;
    } else {
        // all comes good
    }
    while (unit > 0)
    {
        mmu_write16(dad, mmu_read16(sad));
        switch (io->dma_ctrl.dst_ctrl)
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
        switch (io->dma_ctrl.src_ctrl)
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
    if (!(io->dma_ctrl.repeat))
        io->dma_ctrl.enable = 0;
}