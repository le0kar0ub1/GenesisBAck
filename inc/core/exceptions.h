/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _CORE_EXCEPTIONS_H_
# define _CORE_EXCEPTIONS_H_

# include "genesisback.h"
# include "io/log.h"
# include "core/core.h"

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

void exception_raise(enum EXCEPTION_VECTOR, uint32_t hdl);

#endif /* _CORE_EXCEPTIONS_H_ */