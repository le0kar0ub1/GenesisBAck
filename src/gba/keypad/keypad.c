/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "gba/keypad.h"
# include "gba/interrupt.h"
# include "modules/module.h"
# include "mmu/mmu.h"
# include <string.h>

struct keypad_iomem
{
    union
    {
        struct
        {
            uint32_t stat_a : 1;
            uint32_t stat_b : 1;
            uint32_t stat_select : 1;
            uint32_t stat_start : 1;
            uint32_t stat_right : 1;
            uint32_t stat_left : 1;
            uint32_t stat_up : 1;
            uint32_t stat_down : 1;
            uint32_t stat_r : 1;
            uint32_t stat_l : 1;
            uint32_t _reserved1 : 6;
        };
        uint16_t key_status;
    };
    union
    {
        struct
        {
            uint32_t ctrl_a : 1;
            uint32_t ctrl_b : 1;
            uint32_t ctrl_select : 1;
            uint32_t ctrl_start : 1;
            uint32_t ctrl_right : 1;
            uint32_t ctrl_left : 1;
            uint32_t ctrl_up : 1;
            uint32_t ctrl_down : 1;
            uint32_t ctrl_r : 1;
            uint32_t ctrl_l : 1;
            uint32_t _reserved2 : 4;
            uint32_t irq_enable : 1;
            uint32_t irq_cond : 1;
        };
        uint16_t key_ctrl;
    };
};

static struct keypad_iomem *io = NULL;

/**
 * if keypad module has been initialized:
 *    Then set the given key at pressed | released
 * if Keypad irq are enabled:
 *    Then trigger interrupt module
 */
void keypad_trigger_key(uint32_t key, bool type)
{
    if (io) {
        if (key <= KEYPAD_KEY_MAX) {
            if (type == KEYPAD_PRESS_KEY) { // pressed
                io->key_status &= ~(1 << key);
            } else { // released
                io->key_status |= (1 << key);
            }
        }
        if (io->irq_enable) {
            if (
                // OR -> one key is triggered => IRQ
                (!(io->irq_cond)) 
                ||
                (io->irq_cond && (bitfield_readx(io->key_ctrl, 0, 10) & bitfield_readx(io->key_ctrl, 0, 10)) == 0x0)
                // AND -> all enabled keys are pressed => IRQ
            ) {
                interrupt_raise_irq(IRQ_KEYPAD);
            }
        }
    }
}

static void keypad_info(void)
{
    if (io) {
        printf("IRQ %s\n", io->irq_enable ? "enabled" : "disabled");
        printf("IRQ condition: %s\n", io->irq_cond ? "Release" : "Press");
        printf("                               | A  | B  | SELECT | START | RIGHT | LEFT | UP | DOWN | R | L\n");
        printf("-----------------------------------------------------------------------------------------------\n");
        printf(
               "Control (0: Ignore, 1: Select) | %u  | %u  | %u      | %u     | %u     | %u    | %u  | %u    | %u | %u\n",
            io->ctrl_a, io->ctrl_b, io->ctrl_select, io->ctrl_start, io->ctrl_right,
            io->ctrl_left, io->ctrl_up, io->ctrl_down, io->ctrl_r, io->ctrl_l
        );
        printf("-----------------------------------------------------------------------------------------------\n");
        printf(
               "Status (0: press, 1: Release)  | %u  | %u  | %u      | %u     | %u     | %u    | %u  | %u    | %u | %u\n",
            io->stat_a, io->stat_b, io->stat_select, io->stat_start, io->stat_right,
            io->stat_left, io->stat_up, io->stat_down, io->stat_r, io->stat_l
        );
    }
}

/**
 * Initialized all keys to released
 */
static void keypad_init(void)
{
    io = (struct keypad_iomem *)mmu_load_addr(KEYPAD_IOMEM_BASE);
    io->key_status |= ((1 << 10) - 1);
}

static void keypad_exit(void)
{
    io = NULL;
}

static void keypad_reset(void)
{
    keypad_init();
}

REGISTER_MODULE(
    keypad,
    "The keypad of the GBA",
    MODULE_HOOK_GBA,
    keypad_init,
    keypad_exit,
    keypad_reset,
    NULL,
    keypad_info
);