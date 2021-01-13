/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <pthread.h>
# include <endian.h>
# include <stdlib.h>
# include <string.h>
# include <modules/module.h>
# include <mmu/mmu.h>
# include <mmu/trigger.h>

static struct memory *mem;
static pthread_mutex_t mutex;

/**
 * Load the EMULATOR address shifted
 */
void *mmu_load_addr(uint32_t shift)
{
    return (((void *)(mem->raw + shift)));
}

/**
 * Lock the MMU mutex
 */
void mmu_lock(void)
{
    pthread_mutex_lock(&mutex);
}

/**
 * UnLock the MMU mutex
 */
void mmu_unlock(void)
{
    pthread_mutex_unlock(&mutex);
}

/** 
 * TODO: Raise an unaligned exception  
 */
# define is_aligned(addr, on)                   \
    if (addr & (on - 1))                        \
        panic("Unaligned address %#08x", addr); \

/**
 * Read 8bits from the given address
 */
uint8_t mmu_read8(uint32_t addr)
{
    uint8_t val;

    if (addr >= MEMORY_SIZE)
        panic("Segmentation fault: Address %#08x", addr);
    pthread_mutex_lock(&mutex);
    val = mem->raw[addr];
    pthread_mutex_unlock(&mutex);
    return (val);
}

/**
 * Read 16bits from the given address
 */
uint16_t mmu_read16(uint32_t addr)
{
    uint16_t val;

    if (addr >= MEMORY_SIZE - 1)
        panic("Segmentation fault: Address %#08x", addr);
    is_aligned(addr, 2);
    pthread_mutex_lock(&mutex);
    #ifdef __BIG_ENDIAN__
        val = be16toh(*((uint16_t *)(mem->raw + addr)));
    #else
        val = le16toh(*((uint16_t *)(mem->raw + addr)));
    #endif
    pthread_mutex_unlock(&mutex);
    return (val);
}

/**
 * Read 32bits from the given address
 */
uint32_t mmu_read32(uint32_t addr)
{
    uint32_t val;

    if (addr >= MEMORY_SIZE - 3)
        panic("Segmentation fault: Address %#08x", addr);
    is_aligned(addr, 4);
    pthread_mutex_lock(&mutex);
    #ifdef __BIG_ENDIAN__
        val = be32toh(*((uint32_t *)(mem->raw + addr)));
    #else
        val = le32toh(*((uint32_t *)(mem->raw + addr)));
    #endif
    pthread_mutex_unlock(&mutex);
    return (val);
}

/**
 * Write 8bits from the given address
 */
void mmu_write8(uint32_t addr, uint8_t val)
{
    if (addr >= MEMORY_SIZE)
        panic("Segmentation fault: Address %#08x", addr);
    pthread_mutex_lock(&mutex);
    mem->raw[addr] = val;
    mmu_trigger_handle_write(addr, 8 / 8, val);
    pthread_mutex_unlock(&mutex);
}

/**
 * Write 16bits from the given address
 */
void mmu_write16(uint32_t addr, uint16_t val)
{
    if (addr >= MEMORY_SIZE - 1)
        panic("Segmentation fault: Address %#08x", addr);
    is_aligned(addr, 2);
    pthread_mutex_lock(&mutex);
    #ifdef __BIG_ENDIAN__
        *((uint16_t *)(mem->raw + addr)) = htobe16(val);
    #else
        *((uint16_t *)(mem->raw + addr)) = htole16(val);
    #endif
    mmu_trigger_handle_write(addr, 16 / 8, val);
    pthread_mutex_unlock(&mutex);
}

/**
 * Write 32bits from the given address
 */
void mmu_write32(uint32_t addr, uint32_t val)
{
    if (addr >= MEMORY_SIZE - 3)
        panic("Segmentation fault: Address %#08x", addr);
    is_aligned(addr, 4);
    pthread_mutex_lock(&mutex);
    #ifdef __BIG_ENDIAN__
        *((uint32_t *)(mem->raw + addr)) = htobe32(val);
    #else
        *((uint32_t *)(mem->raw + addr)) = htole32(val);
    #endif
    mmu_trigger_handle_write(addr, 32 / 8, val);
    pthread_mutex_unlock(&mutex);
}

/**
 * destroy the memory module
 */
static void mmu_exit(void)
{
    free(mem);
}

/**
 * When reset the machine, reset the memory module
 */
static void mmu_reset(void)
{
    memset(mem->raw, 0x0, MEMORY_SIZE);
}

/**
 * Initialize the memory module
 */
static void mmu_init(void)
{
    mem = malloc(sizeof(struct memory));
    if (!mem) {
        panic("MMU init failed");
    }
    mmu_reset();
}

REGISTER_MODULE(
    mmu,
    "The MMU of the all the emulator core",
    MODULE_HOOK_BOOTSTRAP,
    mmu_init,
    mmu_exit,
    mmu_reset,
    NULL,
    NULL,
    NULL
);