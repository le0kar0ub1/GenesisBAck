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

static pthread_t thread;
static bool kill_thread = false;
static struct dma_iomem *io = NULL;

struct dmax_iomem *dma_get_engine_io(enum DMA_ENGINE engine)
{
    return (
        (struct dmax_iomem *)ADD_PTR(io, DMA_IOMEM_ENGINE_SHIFT(engine))
    );
} 

static void dma_init(void)
{
    io = (struct dma_iomem *)mmu_load_addr(DMA_IOMEM_BASE);
}

static void dma_stop(void)
{
    kill_thread = true;
    pthread_join(thread, NULL);
}

static void dma_exit(void)
{
    if (module_is_running_runmod("dma"))
        dma_stop();
    io = NULL;
}

static void *dma_thread(void *arg __unused)
{
    /**
     * Keep the priority order
     * Only one total transfer is effectuate for a transfer call
     * if the repeat bit is enabled then it will be relauched from here
     */
    while (!kill_thread) {
        while (!kill_thread) {
            if (mmu_safe_check(io->dma0_ctrl.enable)) {
                core_cpu_stop_exec();
                dma0_transfer();
                core_cpu_restart_exec();
            } else if (mmu_safe_check(io->dma1_ctrl.enable)) {
                core_cpu_stop_exec();
                dma1_transfer();
                core_cpu_restart_exec();
            } else if (mmu_safe_check(io->dma2_ctrl.enable)) {
                core_cpu_stop_exec();
                dma2_transfer();
                core_cpu_restart_exec();
            } else if (mmu_safe_check(io->dma3_ctrl.enable)) {
                core_cpu_stop_exec();
                dma3_transfer();
                core_cpu_restart_exec();
            } else {
                break;
            }
        }
        // if (!kill_thread) {
        //     pthread_cond_wait();
        // }
    }
    // pthread_exit(NULL);
    return (NULL);
}

static void dma_start(void)
{
    if (pthread_create(&thread, NULL, dma_thread, NULL) != 0)
        panic("Thread creation failed");
}

static void dma_reset(void)
{
    dma_stop();
    dma_init();
    dma_start();
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
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("DMA0 | %08x | %08x    | %04x  | %u       | %u   | %s     | %s      | %u      | %s\n",
        io->dma0_sad, io->dma0_dad, io->dma0_count, io->dma0_ctrl.enable, io->dma0_ctrl.irq,
        dma_info_addr_manip(io->dma0_ctrl.src_ctrl), dma_info_addr_manip(io->dma0_ctrl.dst_ctrl),
        io->dma0_ctrl.repeat, io->dma0_ctrl.trns_type ? "WORD (4B)" : "HALF-WORD (2B)"
    );
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("DMA1 | %08x | %08x    | %04x  | %u       | %u   | %s     | %s      | %u      | %s\n",
        io->dma1_sad, io->dma1_dad, io->dma1_count, io->dma1_ctrl.enable, io->dma1_ctrl.irq,
        dma_info_addr_manip(io->dma1_ctrl.src_ctrl), dma_info_addr_manip(io->dma1_ctrl.dst_ctrl),
        io->dma1_ctrl.repeat, io->dma1_ctrl.trns_type ? "WORD (4B)" : "HALF-WORD (2B)"
    );
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("DMA2 | %08x | %08x    | %04x  | %u       | %u   | %s     | %s      | %u      | %s\n",
        io->dma2_sad, io->dma2_dad, io->dma2_count, io->dma2_ctrl.enable, io->dma2_ctrl.irq,
        dma_info_addr_manip(io->dma2_ctrl.src_ctrl), dma_info_addr_manip(io->dma2_ctrl.dst_ctrl),
        io->dma2_ctrl.repeat, io->dma2_ctrl.trns_type ? "WORD (4B)" : "HALF-WORD (2B)"
    );
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("DMA3 | %08x | %08x    | %04x  | %u       | %u   | %s     | %s      | %u      | %s\n",
        io->dma3_sad, io->dma3_dad, io->dma3_count, io->dma3_ctrl.enable, io->dma3_ctrl.irq,
        dma_info_addr_manip(io->dma3_ctrl.src_ctrl), dma_info_addr_manip(io->dma3_ctrl.dst_ctrl),
        io->dma3_ctrl.repeat, io->dma3_ctrl.trns_type ? "WORD (4B)" : "HALF-WORD (2B)"
    );
}

REGISTER_MODULE(
    dma,
    "The DMA engines of the GBA",
    MODULE_HOOK_GBA,
    dma_init,
    dma_exit,
    dma_reset,
    dma_start,
    dma_stop,
    dma_info
);

REGISTER_MMU_TRIGGER(
    dma_trigger,
    0x40000B0,
    0x40000E0,
    NULL,
    NULL
);