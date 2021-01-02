/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "soc/keypad.h"
# include "soc/interrupt.h"

static struct keypad_iomem *io = NULL;

void keypad_init(void)
{
    io = (struct keypad_iomem *)KEYPAD_IOMEM_BASE;
}

void keypad_exit(void)
{
    io = NULL;
}

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
                // OR -> one key triggered => IRQ
                (!(io->irq_cond)) 
                ||
                (io->irq_cond && (bitfield_readx(io->key_ctrl, 0, 10) & bitfield_readx(io->key_ctrl, 0, 10)) == 0x0)
                // AND -> all enabled keys pressed => IRQ
            ) {
                interrupt_raise_irq(IRQ_KEYPAD);
            }
        }
    }
}