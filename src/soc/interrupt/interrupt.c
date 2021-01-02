/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "soc/interrupt.h"
# include "core/core.h"
# include "core/exceptions.h"

struct int_master_enable
{
    uint16_t enabled   : 1;
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

static struct interrupt_iomem *io = NULL;

void interrupt_init(void)
{
    io = (struct interrupt_iomem *)INTERRUPT_IOMEM_BASE;
}

void interrupt_exit(void)
{
    io = NULL;
}

/**
 * Are interrupts enabled
 * cpu flag & interrupt master enabled reg
 */
bool interrupt_are_enabled(void)
{
    if (io->int_master_enable.enabled && register_read_cpsr().irq_disable == false)
        return (true);
    return (false);
}

/**
 * Are interrupts enabled & is the given irq enabled ?
 */
bool interrupt_is_irq_enabled(uint32_t irq)
{
    if (interrupt_are_enabled() && bitfield_read1(io->int_enable.raw, irq))
        return (true);
    return (false);
}

/**
 * Raise the given IRQ by mark the given flag to REQUEST
 * then raising an IRQ exception
 */
void interrupt_raise_irq(uint32_t irq)
{
    if (irq > IRQ_MAX)
        panic("Invalid IRQ trigger %u", irq);
    if (interrupt_is_irq_enabled(irq)) {
        if (!bitfield_read1(io->irq_interface.raw, irq)) { // has been ack at previous trigger ?
            io->irq_interface.raw |= (1 << irq);
            exception_raise(EXCEPTION_IRQ, irq);
        }
    }
}

void interrupt_loop(void)
{
    /**
     * TODO: Clear the irq bits when they are wrotten by program
     */
    while (io) {

    }
}