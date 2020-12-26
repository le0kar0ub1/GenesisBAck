/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _GENESISBACK_DEF_H_
# define _GENESISBACK_DEF_H_

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>

/**
 * Types shortcuts
*/
typedef unsigned char       uchar;
typedef unsigned short      ushort;
typedef unsigned int        uint;
typedef unsigned long       ulong;
typedef unsigned long long  ulonglong;

typedef int8_t          int8;
typedef int16_t         int16;
typedef int32_t         int32;
typedef int64_t         int64;
typedef intptr_t        intptr;
typedef intptr_t        ssize_t;

typedef uint8_t         uint8;
typedef uint16_t        uint16;
typedef uint32_t        uint32;
typedef uint64_t        uint64;
typedef uintptr_t       uintptr;

typedef int8_t          s8_t;
typedef int16_t         s16_t;
typedef int32_t         s32_t;
typedef int64_t         s64_t;

typedef uint8_t         u8_t;
typedef uint16_t        u16_t;
typedef uint32_t        u32_t;
typedef uint64_t        u64_t;

typedef void *          hostaddr_t;
typedef uintptr_t       virtaddr_t;
# define PHYSNULL ((physaddr_t)0x0)

typedef uintptr         archv_t;
typedef uintptr *       archp_t;

/**
 * Keyword shortcuts
*/
# define restrict        __restrict
# define __pure          __attribute__((pure))
# define __const         __attribute__((const))
# define __cold          __attribute__((cold))
# define __hot           __attribute__((hot))
# define __used          __attribute__((used))
# define __unused        __attribute__((unused))
# define __packed        __attribute__((packed))
# define __weak          __attribute__((weak))
# define __aligned(x)    __attribute__((aligned(x)))
# define __section(s)    __attribute__((section(s)))
# define __noreturn      __attribute__((noreturn))
# define __expected(x)   __builtin_expect((x), 1)
# define __unexpected(x) __builtin_expect((x), 0)
# define __optimize(x)   __attribute__((optimize(x)))
# define likely(x)       __builtin_expect((x), 1)
# define unlikely(x)     __builtin_expect((x), 0)

# define ANSI_RESET          "\e[0m"

# define ANSI_RED            "\e[31m"
# define ANSI_GREEN          "\e[32m"
# define ANSI_YELLOW         "\e[33m"
# define ANSI_BLUE           "\e[34m"
# define ANSI_MAGENTA        "\e[35m"
# define ANSI_CYAN           "\e[36m"
# define ANSI_LIGHT_GRAY     "\e[37m"
# define ANSI_DARK_GRAY      "\e[90m"
# define ANSI_LIGHT_RED      "\e[91m"
# define ANSI_LIGHT_GREEN    "\e[92m"
# define ANSI_LIGHT_YELLOW   "\e[93m"
# define ANSI_LIGHT_BLUE     "\e[94m"
# define ANSI_LIGHT_MAGENTA  "\e[95m"
# define ANSI_LIGHT_CYAN     "\e[96m"
# define ANSI_WHITE          "\e[97m"

/**
 * align and keep given type 
*/
# define ALIGN(x, y)     ((typeof(x))(((uintptr)(x) + ((y) - 1)) & ~((y) - 1)))

# define ALIGN2(x) (x & 0xFFFFFFFE)
# define ALIGN4(x) (x & 0xFFFFFFFC)

/**
 * Generate the following data in genesisback section 
*/
struct genesisback_data {
    uint32_t blksize;
    uint32_t datasize;
    void *data;
    char const *name;
} __packed;

# define REGISTER_GENESISBACK_DATA(xname, xdata, xdatasize)         \
    __section("genesisback_dat") __used                             \
    static const struct genesisback_data const xname = {            \
        .blksize = sizeof(#xname) + sizeof(void *) + xdatasize,     \
        .datasize = xdatasize,                                      \
        .data = xdata,                                              \
        .name = #xname                                              \
    }

# define ADD_PTR(x, y) ((typeof(x))((uintptr_t)x + (uintptr_t)y))
# define SUB_PTR(x, y) ((typeof(x))((uintptr_t)x - (uintptr_t)y))

# define bitfield_read1(val, bit)  ((bool)(val & (1 << bit)))
# define bitfield_write1(val, bit) (val |= (1 << bit))
// inclusive from, exclusive to
# define bitfield_readx(val, from, to) ((typeof(val))(val << (sizeof(val) * 8 - to) >> (sizeof(val) * 8 - to + from)))

static inline int32_t sign_extend_to_i32(uint32_t val, uint32_t extend)
{
    if ((val & (1 << (extend - 1))) == 0)
        return ((int32_t)val);
    else
        return ((int32_t)(val | (((1 << (32 - extend)) - 1) << 11)));
}

# define sign_extend11_to_i32(val) sign_extend_to_i32(val, 11)
# define sign_extend12_to_i32(val) sign_extend_to_i32(val, 12)
# define sign_extend24_to_i32(val) sign_extend_to_i32(val, 24)

# define mask_low(x) ((1 << x) - 1)

#endif /* !_GENESISBACK_DEF_H_ */
