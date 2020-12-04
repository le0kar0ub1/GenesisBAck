/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _MACHINE_SHARED_CPU_H_
# define _MACHINE_SHARED_CPU_H_

# include "genesisback.h"

/**
 * A basic wide 32 bits register
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

static_assert(sizeof(struct register32) == 4);

/**
 * A basic wide 64 bits register
 */
struct register64
{
    union
    {
        union
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
            uint32_t _reserved32;
        };
        uint64_t r64;
    };
};

static_assert(sizeof(struct register64) == 8);

#endif /* _MACHINE_SHARED_CPU_H_ */