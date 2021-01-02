/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _SOC_KEYPAD_H_
# define _SOC_KEYPAD_H_

# include "genesisback.h"

# define KEYPAD_IOMEM_BASE 0x4000130

enum {
    KEYPAD_KEY_A = 0,
    KEYPAD_KEY_B = 1,
    KEYPAD_KEY_SELECT = 2,
    KEYPAD_KEY_START = 3,
    KEYPAD_KEY_RIGHT = 4,
    KEYPAD_KEY_LEFT = 5,
    KEYPAD_KEY_UP = 6,
    KEYPAD_KEY_DOWN = 7,
    KEYPAD_KEY_R = 8,
    KEYPAD_KEY_L = 9,
    KEYPAD_KEY_MAX = 9
};

enum {
    KEYPAD_PRESS_KEY = 0,
    KEYPAD_RELEASE_KEY = 1
};

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

void keypad_init(void);
void keypad_exit(void);
void keypad_trigger_key(uint32_t key, bool type);

#endif /* _SOC_KEYPAD_H_ */