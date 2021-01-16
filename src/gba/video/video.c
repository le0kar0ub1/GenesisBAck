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

static void video_init(void) {}

static void video_exit(void) {}

static void video_reset(void) {}

static void video_info(void) {}

REGISTER_MODULE(
    video,
    "LCD emulation",
    MODULE_HOOK_GBA,
    video_init,
    video_exit,
    video_reset,
    NULL,
    NULL,
    video_info
);