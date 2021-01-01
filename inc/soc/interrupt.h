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

struct int_master_enable
{
    uint16_t enable    : 1;
    uint16_t _reserved : 15;
};

struct irq_flags
{
    union
    {
        struct
        {
            uint16_t lcd_v_blank     : 1;
            uint16_t lcd_h_blank     : 1;
            uint16_t lcd_v_counter   : 1;
            uint16_t timer0_overflow : 1;
            uint16_t timer1_overflow : 1;
            uint16_t timer2_overflow : 1;
            uint16_t timer3_overflow : 1;
            uint16_t serial_com      : 1;
            uint16_t dma0            : 1;
            uint16_t dma1            : 1;
            uint16_t dma2            : 1;
            uint16_t dma3            : 1;
            uint16_t keypad          : 1;
            uint16_t gamepak         : 1;
            uint16_t _reserved1      : 2;
        };
        uint16_t raw;
    };
};

static_assert(sizeof(struct irq_flags) == sizeof(uint16_t));

struct interrupt_iomem
{
    struct irq_flags int_enable;        /* Interrupt Enable Register */
    struct irq_flags irq_interface;     /* Interrupt Request Flags / IRQ Acknowledge */
    uint16_t  _reserved1;               /* Not used */
    uint16_t  _reserved2;               /* Not used */
    struct int_master_enable int_master_enable; /* Interrupt Master Enable Register */
};

void interrupt_init(void);
void interrupt_exit(void);
void interrupt_loop(void);
void interrupt_raise_irq(uint32_t irq);
bool interrupt_are_enabled(void);
bool interrupt_is_irq_enabled(uint32_t irq);

#endif /* _SOC_INTERRUPT_H_ */