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

static struct interrupt_iomem *io = NULL;

void interrupt_init(void)
{
    io = (struct interrupt_iomem *)INTERRUPT_IOMEM_BASE;
}

void interrupt_exit(void)
{
    io = NULL;
}

bool interrupt_are_enabled(void)
{
    if (io->int_master_enable.enable && register_read_cpsr().irq_disable == false)
        return (true);
    return (false);
}

bool interrupt_is_irq_enabled(uint32_t irq)
{
    if (interrupt_are_enabled() && bitfield_read1(io->int_enable.raw, irq))
        return (true);
    return (false);
}

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