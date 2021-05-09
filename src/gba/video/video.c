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

static void video_info(void)
{
    struct LCD_CTRL lcd_ctrl;
    lcd_ctrl.raw = mmu_read16(VIDEO_IOMEM_DISPCNT);
    printf("/********* LCD CONTROL *********/\n");
    printf("* BG Mode:                    %d *\n", lcd_ctrl.bg_mode);
    printf("* CGB Mode:                   %d *\n", lcd_ctrl.cgb_mode);
    printf("* Display Frame Select:       %d *\n", lcd_ctrl.display_frame);
    printf("* H-Blank Interval free:      %d *\n", lcd_ctrl.hblank_interval_free);
    printf("* OBJ Character VRAM Mapping: %d *\n", lcd_ctrl.obj_char_vram_mapping);
    printf("* Forced Blank:               %d *\n", lcd_ctrl.forced_blank);
    printf("* Screen Display BG0:         %d *\n", lcd_ctrl.screen_display_bg0);
    printf("* Screen Display BG1:         %d *\n", lcd_ctrl.screen_display_bg1);
    printf("* Screen Display BG2:         %d *\n", lcd_ctrl.screen_display_bg2);
    printf("* Screen Display BG3:         %d *\n", lcd_ctrl.screen_display_bg3);
    printf("* Screen Display OBJ:         %d *\n", lcd_ctrl.screen_display_obj);
    printf("* Window 0 Display Flag:      %d *\n", lcd_ctrl.win0_display_flag);
    printf("* Window 1 Display Flag:      %d *\n", lcd_ctrl.win1_display_flag);
    printf("* OBJ Window Display Flag:    %d *\n", lcd_ctrl.winobj_display_flag);
    printf("/*******************************/\n");
}

REGISTER_MODULE(
    video,
    "LCD control but not rendering",
    MODULE_HOOK_GBA,
    video_init,
    video_exit,
    video_reset,
    NULL,
    NULL,
    video_info
);