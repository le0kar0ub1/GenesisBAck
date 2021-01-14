/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <pthread.h>
# include <signal.h>
# include <modules/module.h>
# include <core/core.h>
# include <mmu/mmu.h>
# include <mmu/trigger.h>
# include <gba/dma.h>

/**
 * We can use external MMU pointer for the dma transfers because the cpu is stopped during the process
 */
static struct dma_iomem *io = NULL;

static void dma_init(void)
{
    io = (struct dma_iomem *)mmu_load_addr(DMA_IOMEM_BASE);
}

static void dma_exit(void)
{
    io = NULL;
}

static void dma_mmu_trigger_exec(struct mmhit hit __unused)
{
    /**
     * Keep the priority order
     * Only one total transfer is effectuate for a transfer call
     * if the repeat bit is enabled then it will be relauched from here
     */
    while (io) {
        if (mmu_safe_check(io->dma0_ctrl.enable)) {
            dma0_transfer();
        } else if (mmu_safe_check(io->dma1_ctrl.enable)) {
            dma1_transfer();
        } else if (mmu_safe_check(io->dma2_ctrl.enable)) {
            dma2_transfer();
        } else if (mmu_safe_check(io->dma3_ctrl.enable)) {
            dma3_transfer();
        } else {
            break;
        }
    }
}

static bool dma_mmu_trigger_check(struct mmhit hit)
{
    uint32_t range = 1;

# define DMA_TRIGGER_CHECK_LAZY(eng)                        \
    if (                                                    \
        hit.addr <= DMA_IOMEM_GETADDR(eng, 0xA) &&          \
        hit.addr + hit.size >= DMA_IOMEM_GETADDR(eng, 0xA)  \
    ) {                                                     \
        range += DMA_IOMEM_GETADDR(eng, 0xA) - hit.addr;    \
        if ((bool)(hit.val >> ((range * 8) - 1)) == true)   \
            return (true);                                  \
    }

    DMA_TRIGGER_CHECK_LAZY(0);
    DMA_TRIGGER_CHECK_LAZY(1);
    DMA_TRIGGER_CHECK_LAZY(2);
    DMA_TRIGGER_CHECK_LAZY(3);

#undef DMA_TRIGGER_CHECK_LAZY

    return (false);
}

static void dma_reset(void)
{
    dma_init();
}

static inline char const *dma_info_addrmanip_sad(uint32_t ctrl)
{
    switch (ctrl)
    {
        case 0b00: return ("increment");
        case 0b01: return ("decrement");
        case 0b10: return ("fixed");
        case 0b11: default: return ("prohibited");
    }
}

static inline char const *dma_info_addrmanip_dad(uint32_t ctrl)
{
    switch (ctrl)
    {
        case 0b00: return ("increment");
        case 0b01: return ("decrement");
        case 0b10: return ("fixed");
        case 0b11: default: return ("inc/reload");
    }
}

static inline char const *dma_info_timing(uint32_t tim)
{
    switch (tim)
    {
        case 0b00: return ("immediate");
        case 0b01: return ("V-Blank");
        case 0b10: return ("H-Blank");
        case 0b11: default: return ("Special");
    }
}

static void dma_info(void)
{
    printf("     | Source   | Destination | Count | Enabled | IRQ | SrcCtrl        | DestCtrl        | Repeat | Timing     | Type\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
    printf("DMA0 | %08x | %08x    | %04x  | %u       | %u   | %-10s     | %-10s      | %u      | %-10s | %s\n",
        io->dma0_sad, io->dma0_dad, io->dma0_count, io->dma0_ctrl.enable, io->dma0_ctrl.irq,
        dma_info_addrmanip_sad(io->dma0_ctrl.src_ctrl), dma_info_addrmanip_dad(io->dma0_ctrl.dst_ctrl),
        io->dma0_ctrl.repeat, dma_info_timing(io->dma0_ctrl.timing), io->dma0_ctrl.trns_type ? "WORD (4B)" : "HALF-WORD (2B)"
    );
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
    printf("DMA1 | %08x | %08x    | %04x  | %u       | %u   | %-10s     | %-10s      | %u      | %-10s | %s\n",
        io->dma1_sad, io->dma1_dad, io->dma1_count, io->dma1_ctrl.enable, io->dma1_ctrl.irq,
        dma_info_addrmanip_sad(io->dma1_ctrl.src_ctrl), dma_info_addrmanip_dad(io->dma1_ctrl.dst_ctrl),
        io->dma1_ctrl.repeat, dma_info_timing(io->dma1_ctrl.timing), io->dma1_ctrl.trns_type ? "WORD (4B)" : "HALF-WORD (2B)"
    );
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
    printf("DMA2 | %08x | %08x    | %04x  | %u       | %u   | %-10s     | %-10s      | %u      | %-10s | %s\n",
        io->dma2_sad, io->dma2_dad, io->dma2_count, io->dma2_ctrl.enable, io->dma2_ctrl.irq,
        dma_info_addrmanip_sad(io->dma2_ctrl.src_ctrl), dma_info_addrmanip_dad(io->dma2_ctrl.dst_ctrl),
        io->dma2_ctrl.repeat, dma_info_timing(io->dma2_ctrl.timing), io->dma2_ctrl.trns_type ? "WORD (4B)" : "HALF-WORD (2B)"
    );
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
    printf("DMA3 | %08x | %08x    | %04x  | %u       | %u   | %-10s     | %-10s      | %u      | %-10s | %s\n",
        io->dma3_sad, io->dma3_dad, io->dma3_count, io->dma3_ctrl.enable, io->dma3_ctrl.irq,
        dma_info_addrmanip_sad(io->dma3_ctrl.src_ctrl), dma_info_addrmanip_dad(io->dma3_ctrl.dst_ctrl),
        io->dma3_ctrl.repeat, dma_info_timing(io->dma3_ctrl.timing), io->dma3_ctrl.trns_type ? "WORD (4B)" : "HALF-WORD (2B)"
    );
}

REGISTER_MODULE(
    dma,
    "The DMA engines of the GBA",
    MODULE_HOOK_GBA,
    dma_init,
    dma_exit,
    dma_reset,
    NULL,
    NULL,
    dma_info
);

REGISTER_MMU_TRIGGER(
    &dma,
    0x40000B0,
    0x40000E0,
    dma_mmu_trigger_check,
    dma_mmu_trigger_exec
);