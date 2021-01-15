/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <modules/module.h>
# include <mmu/mmu.h>
# include <mmu/trigger.h>
# include <gba/interrupt.h>
# include <core/core.h>
# include <core/exceptions.h>
# include <pthread.h>

struct int_master_enable
{
    union
    {
        struct
        {
            uint16_t enabled   : 1;
            uint16_t _reserved : 15;
        };
        uint16_t raw;
    };
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

# define INTERRUPT_IOMEM_BASE 0x4000200

enum {
    IRQ_ENABLE_ADDR        = INTERRUPT_IOMEM_BASE + 0x0,
    IRQ_INTERFACE_ADDR     = INTERRUPT_IOMEM_BASE + 0x2,
    INT_MASTER_ENABLE_ADDR = INTERRUPT_IOMEM_BASE + 0x8
};

# define read_int_master_enable() ((bool)(mmu_read16(INT_MASTER_ENABLE_ADDR) & 0b1))
# define read_irq_enable(irq)     ((bool)(mmu_read16(IRQ_ENABLE_ADDR) & (1 << irq)))
# define read_irq_interface(irq)  ((bool)(mmu_read16(IRQ_INTERFACE_ADDR) & (1 << irq)))

static bool kill_thread = false;

/**
 * Are interrupts enabled
 * cpu flag & interrupt master enabled reg
 */
bool interrupt_are_enabled(void)
{
    if (read_int_master_enable() && register_read_cpsr().irq_disable == false)
        return (true);
    return (false);
}

/**
 * Are interrupts enabled & is the given irq enabled ?
 */
bool interrupt_is_irq_enabled(uint32_t irq)
{
    if (interrupt_are_enabled() && read_irq_enable(irq))
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
        if (!read_irq_interface(irq)) { // has been ack at previous trigger ?
            uint16_t val = mmu_read16(IRQ_INTERFACE_ADDR);
            val |= (1 << irq);
            mmu_raw_write16(IRQ_INTERFACE_ADDR, val);
            exception_raise(EXCEPTION_IRQ, irq);
        }
    }
}

static void interrupt_mmu_trigger(struct mmhit hit)
{
    /**
     * Clear the irq bits when write 1
     */        
    switch (hit.size)
    {
        case 1:
            mmu_raw_write8(hit.addr, mmu_read8(hit.addr) ^ hit.val);
            break;
        case 2:
            mmu_raw_write16(hit.addr, mmu_read16(hit.addr) ^ hit.val);
            break;
        case 4: 
            mmu_raw_write32(hit.addr, mmu_read32(hit.addr) ^ hit.val);
            break;
        default:
            panic("Interrupt clear bit trigger invalid write size");
    }
}

static void interrupt_info(void)
{
    if (module_is_initialized_runmod("interrupt")) {
        printf("IRQ ioreg master %s\n", read_int_master_enable() ? "enabled" : "disabled");
        printf("IRQ cpu master %s\n\n", !(register_read_cpsr().irq_disable) ? "enabled" : "disabled");
        printf("        | LCD V BLANK | LCD H BLANK | LCD V COUNTER | TIMER0 | TIMER1 | TIMER2 | TIMER3 | SERIAL | DMA0 | DMA1 | DMA2 | DMA3 | KEYPAD | GAMEPAK\n");
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf(
               "Enabled | %u           | %u           | %u             | %u      | %u      | %u      | %u      | %u      | %u    | %u    | %u    | %u    | %u      | %u\n",
            read_irq_enable(IRQ_LCD_V_BLANK), read_irq_enable(IRQ_LCD_H_BLANK), read_irq_enable(IRQ_LCD_V_COUNTER), read_irq_enable(IRQ_TIMER0_OVERFLOW), read_irq_enable(IRQ_TIMER1_OVERFLOW),
            read_irq_enable(IRQ_TIMER2_OVERFLOW), read_irq_enable(IRQ_TIMER3_OVERFLOW), read_irq_enable(IRQ_SERIAL_COM), read_irq_enable(IRQ_DMA0), read_irq_enable(IRQ_DMA1), read_irq_enable(IRQ_DMA2),
            read_irq_enable(IRQ_DMA3), read_irq_enable(IRQ_KEYPAD), read_irq_enable(IRQ_GAMEPAK)
        );
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf(
               "REQ/ACK | %u           | %u           | %u             | %u      | %u      | %u      | %u      | %u      | %u    | %u    | %u    | %u    | %u      | %u\n",
            read_irq_interface(IRQ_LCD_V_BLANK), read_irq_interface(IRQ_LCD_H_BLANK), read_irq_interface(IRQ_LCD_V_COUNTER), read_irq_interface(IRQ_TIMER0_OVERFLOW), read_irq_interface(IRQ_TIMER1_OVERFLOW),
            read_irq_interface(IRQ_TIMER2_OVERFLOW), read_irq_interface(IRQ_TIMER3_OVERFLOW), read_irq_interface(IRQ_SERIAL_COM), read_irq_interface(IRQ_DMA0), read_irq_interface(IRQ_DMA1), read_irq_interface(IRQ_DMA2),
            read_irq_interface(IRQ_DMA3), read_irq_interface(IRQ_KEYPAD), read_irq_interface(IRQ_GAMEPAK)
        );
    }
}

static void interrupt_init(void)
{
}

static void interrupt_exit(void)
{
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

REGISTER_MMU_TRIGGER(
    &interrupt,
    0x4000202,
    0x4000204,
    NULL,
    interrupt_mmu_trigger
);