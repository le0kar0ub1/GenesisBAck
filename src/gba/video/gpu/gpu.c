/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <core/core.h>
# include <gba/video.h>
# include <gba/interrupt.h>
# include <modules/module.h>
# include <mmu/mmu.h>
# include <mmu/trigger.h>

static void gpu_init(void) {}

static void gpu_exit(void) {}

static void gpu_reset(void) {}

static void gpu_info(void) {}

REGISTER_MODULE(
    gpu,
    "Render the video",
    MODULE_HOOK_GBA,
    gpu_init,
    gpu_exit,
    gpu_reset,
    NULL,
    NULL,
    gpu_info
);