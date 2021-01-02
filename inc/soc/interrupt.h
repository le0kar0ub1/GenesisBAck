/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _SOC_INTERRUPT_H_
# define _SOC_INTERRUPT_H_

# include "genesisback.h"

# define INTERRUPT_IOMEM_BASE 0x4000200

enum {
    IRQ_LCD_V_BLANK = 0,
    IRQ_LCD_H_BLANK = 1,
    IRQ_LCD_V_COUNTER = 2,
    IRQ_TIMER0_OVERFLOW = 3,
    IRQ_TIMER1_OVERFLOW = 4,
    IRQ_TIMER2_OVERFLOW = 5,
    IRQ_TIMER3_OVERFLOW = 6,
    IRQ_SERIAL_COM = 7,
    IRQ_DMA0 = 8,
    IRQ_DMA1 = 9,
    IRQ_DMA2 = 10,
    IRQ_DMA3 = 11,
    IRQ_KEYPAD = 12,
    IRQ_GAMEPAK = 13,
    IRQ_MAX = 13
};

void interrupt_init(void);
void interrupt_exit(void);
void interrupt_loop(void);
void interrupt_raise_irq(uint32_t irq);
bool interrupt_are_enabled(void);
bool interrupt_is_irq_enabled(uint32_t irq);

#endif /* _SOC_INTERRUPT_H_ */