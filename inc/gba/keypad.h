/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _GBA_KEYPAD_H_
# define _GBA_KEYPAD_H_

# include <genesisback.h>

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

void keypad_trigger_key(uint32_t key, bool type);

#endif /* _GBA_KEYPAD_H_ */