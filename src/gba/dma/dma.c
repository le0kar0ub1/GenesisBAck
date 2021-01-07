/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "modules/module.h"
# include "mmu/mmu.h"
# include "gba/dma.h"

static struct dma_iomem *io = NULL;

static void dma_init(void)
{
    io = (struct dma_iomem *)mmu_load_addr(DMA_IOMEM_BASE);
    // dma0_init();
    // dma1_init();
    // dma2_init();
    // dma3_init();
}

static void dma_exit(void)
{
    // dma0_exit();
    // dma1_exit();
    // dma2_exit();
    // dma3_exit();
}

static void dma_reset(void)
{
    dma_init();
}

static inline char const *dma_info_addr_manip(uint32_t ctrl)
{
    switch (ctrl)
    {
        case 0b00: return ("inc");
        case 0b01: return ("dec");
        case 0b10: return ("fix");
        case 0b11: default: return ("nop");
    }
}

static void dma_info(void)
{
    printf("     | Source   | Destination | Count | Enabled | IRQ | SrcCtrl | DestCtrl | Repeat | Type\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("DMA0 | %08x | %08x    | %04x  | %u       | %u   | %s     | %s      | %u      | %s\n",
        io->dma0_sad, io->dma0_dad, io->dma0_count, io->dma0_ctrl.enable, io->dma0_ctrl.irq,
        dma_info_addr_manip(io->dma0_ctrl.src_ctrl), dma_info_addr_manip(io->dma0_ctrl.dst_ctrl),
        io->dma0_ctrl.repeat, io->dma0_ctrl.trns_type ? "4B" : "2B"
    );
    printf("---------------------------------------------------------------------------------------------\n");
    printf("DMA1 | %08x | %08x    | %04x  | %u       | %u   | %s     | %s      | %u      | %s\n",
        io->dma1_sad, io->dma1_dad, io->dma1_count, io->dma1_ctrl.enable, io->dma1_ctrl.irq,
        dma_info_addr_manip(io->dma1_ctrl.src_ctrl), dma_info_addr_manip(io->dma1_ctrl.dst_ctrl),
        io->dma1_ctrl.repeat, io->dma1_ctrl.trns_type ? "4B" : "2B"
    );
    printf("---------------------------------------------------------------------------------------------\n");
    printf("DMA2 | %08x | %08x    | %04x  | %u       | %u   | %s     | %s      | %u      | %s\n",
        io->dma2_sad, io->dma2_dad, io->dma2_count, io->dma2_ctrl.enable, io->dma2_ctrl.irq,
        dma_info_addr_manip(io->dma2_ctrl.src_ctrl), dma_info_addr_manip(io->dma2_ctrl.dst_ctrl),
        io->dma2_ctrl.repeat, io->dma2_ctrl.trns_type ? "4B" : "2B"
    );
    printf("---------------------------------------------------------------------------------------------\n");
    printf("DMA3 | %08x | %08x    | %04x  | %u       | %u   | %s     | %s      | %u      | %s\n",
        io->dma3_sad, io->dma3_dad, io->dma3_count, io->dma3_ctrl.enable, io->dma3_ctrl.irq,
        dma_info_addr_manip(io->dma3_ctrl.src_ctrl), dma_info_addr_manip(io->dma3_ctrl.dst_ctrl),
        io->dma3_ctrl.repeat, io->dma3_ctrl.trns_type ? "4B" : "2B"
    );
}

REGISTER_MODULE(
    dma,
    "The DMA engine of the GBA",
    MODULE_HOOK_GBA,
    dma_init,
    dma_exit,
    dma_reset,
    NULL,
    dma_info
);