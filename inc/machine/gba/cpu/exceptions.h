/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _MACHINE_GBA_ARM7TDMI_EXCEPTIONS_H_
# define _MACHINE_GBA_ARM7TDMI_EXCEPTIONS_H_

# include "genesisback.h"
# include "machine/gba/gba.h"
# include "io/log.h"
# include "machine/gba/cpu/core.h"

# define EXCEPTION_VECTOR_BASE 0x0

enum EXCEPTION_VECTOR
{
    EXCEPTION_RESET        = EXCEPTION_VECTOR_BASE + 0x0,
    EXCEPTION_UND_INSTR    = EXCEPTION_VECTOR_BASE + 0x4,
    EXCEPTION_SWI          = EXCEPTION_VECTOR_BASE + 0x8,
    EXCEPTION_PREFETCH_ABT = EXCEPTION_VECTOR_BASE + 0xC,
    EXCEPTION_DATA_ABT     = EXCEPTION_VECTOR_BASE + 0x10,
    EXCEPTION_ADDR_EXCEED  = EXCEPTION_VECTOR_BASE + 0x14,
    EXCEPTION_IRQ          = EXCEPTION_VECTOR_BASE + 0x18,
    EXCEPTION_FIQ          = EXCEPTION_VECTOR_BASE + 0x1C
};

#undef EXCEPTION_VECTOR_BASE

struct cpu_exception_vector_trait
{
    uint32_t address;    // vectoro address
    uint32_t priority;   // priority compared to others ones
    uint32_t opmode;     // operation mode while taking the given exception
    bool is_irq_disable; // 1 if the flag irq_disable must be set to 1, no action else 
    bool is_fiq_disable; // 1 if the flag fiq_disable must be set to 1, no action else 
};

void cpu_exception_raise(enum EXCEPTION_VECTOR);

#endif /* _MACHINE_GBA_ARM7TDMI_EXCEPTIONS_H_ */