/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "modules/module.h"
# include "mmu/mmu.h"
# include "gba/interrupt.h"
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
    struct irq_flags irq_enable;        /* Interrupt Enable Register */
    struct irq_flags irq_interface;     /* Interrupt Request Flags / IRQ Acknowledge */
    uint16_t  _reserved1;               /* Not used */
    uint16_t  _reserved2;               /* Not used */
    struct int_master_enable int_master_enable; /* Interrupt Master Enable Register */
};

static struct interrupt_iomem *io = NULL;

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
    if (interrupt_are_enabled() && bitfield_read1(io->irq_enable.raw, irq))
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
        panic("Invalid IRQ triggered %u", irq);
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

static void interrupt_info(void)
{
    if (io) {
        printf("IRQ ioreg master %s\n", io->int_master_enable.enabled ? "enabled" : "disabled");
        printf("IRQ cpu master %s\n\n", !(register_read_cpsr().irq_disable) ? "enabled" : "disabled");
        printf("        | LCD V BLANK | LCD H BLANK | LCD V COUNTER | TIMER0 | TIMER1 | TIMER2 | TIMER3 | SERIAL | DMA0 | DMA1 | DMA2 | DMA3 | KEYPAD | GAMEPAK\n");
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf(
               "Enabled | %u           | %u           | %u             | %u      | %u      | %u      | %u      | %u      | %u    | %u    | %u    | %u    | %u      | %u\n",
            io->irq_enable.lcd_v_blank, io->irq_enable.lcd_h_blank, io->irq_enable.lcd_v_counter, io->irq_enable.timer0_overflow, io->irq_enable.timer1_overflow,
            io->irq_enable.timer2_overflow, io->irq_enable.timer3_overflow, io->irq_enable.serial_com, io->irq_enable.dma0, io->irq_enable.dma1, io->irq_enable.dma2,
            io->irq_enable.dma3, io->irq_enable.keypad, io->irq_enable.gamepak
        );
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf(
               "REQ/ACK | %u           | %u           | %u             | %u      | %u      | %u      | %u      | %u      | %u    | %u    | %u    | %u    | %u      | %u\n",
            io->irq_interface.lcd_v_blank, io->irq_interface.lcd_h_blank, io->irq_interface.lcd_v_counter, io->irq_interface.timer0_overflow, io->irq_interface.timer1_overflow,
            io->irq_interface.timer2_overflow, io->irq_interface.timer3_overflow, io->irq_interface.serial_com, io->irq_interface.dma0, io->irq_interface.dma1, io->irq_interface.dma2,
            io->irq_interface.dma3, io->irq_interface.keypad, io->irq_interface.gamepak
        );
    }
}

static void interrupt_init(void)
{
    io = (struct interrupt_iomem *)mmu_load_addr(INTERRUPT_IOMEM_BASE);
}

static void interrupt_exit(void)
{
    io = NULL;
}

static void interrupt_reset(void)
{
    interrupt_init();
}

REGISTER_MODULE(
    interrupt,
    "The interrupt controller of the GBA",
    MODULE_HOOK_GBA,
    interrupt_init,
    interrupt_exit,
    interrupt_reset,
    NULL,
    NULL,
    interrupt_info
);