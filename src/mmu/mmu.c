/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <endian.h>
# include <stdlib.h>
# include <string.h>
# include "mmu/mmu.h"

struct memory *mem;

/**
 * Initialize the memory module
 */
bool mmu_init(void)
{
    mem = malloc(sizeof(struct memory));
    if (!mem) {
        LOG_ERR("Memory initialization failed");
        return (false);
    }
    mmu_reset();
    return (true);
}

/**
 * destroy the memory module
 */
void mmu_exit(void)
{
    free(mem);
}

/**
 * When reset the machine, reset the memory module
 */
void mmu_reset(void)
{
    memset(mem->raw, 0x0, MEMORY_SIZE);
}

/** 
 * TODO: Raise an unaligned exception  
 */
static inline void is_aligned(uint32_t addr, uint8_t on)
{
    if (addr & (on - 1))
        panic("Unaligned address %#08x", addr);
}

/**
 * Read 8bits from the given address
 */
uint8_t mmu_read8(uint32_t addr)
{
    if (addr >= MEMORY_SIZE)
        panic("Segmentation fault: Address %#08x", addr);
    return (mem->raw[addr]);
}

/**
 * Read 16bits from the given address
 */
uint16_t mmu_read16(uint32_t addr)
{
    if (addr >= MEMORY_SIZE - 1)
        panic("Segmentation fault: Address %#08x", addr);
    is_aligned(addr, 2);
    #ifdef __BIG_ENDIAN__
        return be16toh(*((uint16_t *)(mem->raw + addr)));
    #else
        return le16toh(*((uint16_t *)(mem->raw + addr)));
    #endif
}

/**
 * Read 32bits from the given address
 */
uint32_t mmu_read32(uint32_t addr)
{
    if (addr >= MEMORY_SIZE - 3)
        panic("Segmentation fault: Address %#08x", addr);
    is_aligned(addr, 4);
    #ifdef __BIG_ENDIAN__
        return be32toh(*((uint32_t *)(mem->raw + addr)));
    #else
        return le32toh(*((uint32_t *)(mem->raw + addr)));
    #endif
}

/**
 * Write 8bits from the given address
 */
void mmu_write8(uint32_t addr, uint8_t val)
{
    if (addr >= MEMORY_SIZE)
        panic("Segmentation fault: Address %#08x", addr);
    mem->raw[addr] = val;
}

/**
 * Write 16bits from the given address
 */
void mmu_write16(uint32_t addr, uint16_t val)
{
    if (addr >= MEMORY_SIZE - 1)
        panic("Segmentation fault: Address %#08x", addr);
    is_aligned(addr, 2);
    #ifdef __BIG_ENDIAN__
        *((uint16_t *)(mem->raw + addr)) = htobe16(val);
    #else
        *((uint16_t *)(mem->raw + addr)) = htole16(val);
    #endif
}

/**
 * Write 32bits from the given address
 */
void mmu_write32(uint32_t addr, uint32_t val)
{
    if (addr >= MEMORY_SIZE - 3)
        panic("Segmentation fault: Address %#08x", addr);
    is_aligned(addr, 4);
    #ifdef __BIG_ENDIAN__
        *((uint32_t *)(mem->raw + addr)) = htobe32(val);
    #else
        *((uint32_t *)(mem->raw + addr)) = htole32(val);
    #endif
}