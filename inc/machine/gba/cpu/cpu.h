/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _MACHINE_GBA_CPU_H_
# define _MACHINE_GBA_CPU_H_

# include "genesisback.h"
# include <stdint.h>
# include "machine/gba/gba.h"

/**
 * The cpu has to deal with these type of data only
 */
typedef uint8_t   byte_t;
typedef uint16_t  hword_t;
typedef uint32_t  word_t;

/**
 * Define the 2 processor states
 */
enum a {
    PROCESSOR_STATE_ARM,
    PROCESSOR_STATE_THUMB
};

/**
 * Define the 7 operations modes of the processor
 */
enum b {
    PROCESSOR_OPERATION_MODE_USER = 0,
    PROCESSOR_OPERATION_MODE_FIQ = 1,
    PROCESSOR_OPERATION_MODE_IRQ = 2, 
    PROCESSOR_OPERATION_MODE_SUPERVISOR = 3,
    PROCESSOR_OPERATION_MODE_ABORT = 4, 
    PROCESSOR_OPERATION_MODE_SYSTEM = 5,
    PROCESSOR_OPERATION_MODE_UNDEFINED = 6
};

/**
 * The cpu registers list, different 
 */
struct register32
{
    union
    {
        union
        {
            union
            {
                struct
                {
                    uint8_t r8;
                    uint8_t _reserved8;
                };
                uint16_t r16;
            };
            uint16_t _reserverd16;
        };
        uint32_t r32;
    };
};

#endif /* _MACHINE_GBA_CPU_H_ */