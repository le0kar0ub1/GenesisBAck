/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _MMU_MMU_H_
# define _MMU_MMU_H_

# include <genesisback.h>

enum {
    MMU_AREA_BASE_BIOS_ROM = 0x00000000,
    MMU_AREA_END_BIOS_ROM = 0x00003FFF,
    MMU_AREA_SIZE_BIOS_ROM = MMU_AREA_END_BIOS_ROM - MMU_AREA_BASE_BIOS_ROM,
    MMU_AREA_BASE_WRAM_BOARD = 0x02000000,
    MMU_AREA_END_WRAM_BOARD = 0x0203FFFF,
    MMU_AREA_SIZE_WRAM_BOARD = MMU_AREA_END_WRAM_BOARD - MMU_AREA_BASE_WRAM_BOARD,
    MMU_AREA_BASE_WRAM_CHIP = 0x03000000,
    MMU_AREA_END_WRAM_CHIP = 0x03007FFF,
    MMU_AREA_SIZE_WRAM_CHIP = MMU_AREA_END_WRAM_CHIP - MMU_AREA_BASE_WRAM_CHIP,
    MMU_AREA_BASE_IOREG = 0x04000000,
    MMU_AREA_END_IOREG = 0x040003FE,
    MMU_AREA_SIZE_IOREG = MMU_AREA_END_IOREG - MMU_AREA_BASE_IOREG,
    MMU_AREA_BASE_PRAM = 0x05000000,
    MMU_AREA_END_PRAM = 0x050003FF,
    MMU_AREA_SIZE_PRAM = MMU_AREA_END_PRAM - MMU_AREA_BASE_PRAM,
    MMU_AREA_BASE_VRAM = 0x06000000,
    MMU_AREA_END_VRAM = 0x06017FFF,
    MMU_AREA_SIZE_VRAM = MMU_AREA_END_VRAM - MMU_AREA_BASE_VRAM,
    MMU_AREA_BASE_OAM = 0x07000000,
    MMU_AREA_END_OAM = 0x070003FF,
    MMU_AREA_SIZE_OAM = MMU_AREA_END_OAM - MMU_AREA_BASE_OAM,
    MMU_AREA_BASE_ROM0 = 0x08000000,
    MMU_AREA_END_ROM0 = 0x09FFFFFF,
    MMU_AREA_SIZE_ROM0 = MMU_AREA_END_ROM0 - MMU_AREA_BASE_ROM0,
    MMU_AREA_BASE_ROM1 = 0x0A000000,
    MMU_AREA_END_ROM1 = 0x0BFFFFFF,
    MMU_AREA_SIZE_ROM1 = MMU_AREA_END_ROM1 - MMU_AREA_BASE_ROM1,
    MMU_AREA_BASE_ROM2 = 0x0C000000,
    MMU_AREA_END_ROM2 = 0x0DFFFFFF,
    MMU_AREA_SIZE_ROM2 = MMU_AREA_END_ROM2 - MMU_AREA_BASE_ROM2,
    MMU_AREA_BASE_SRAM = 0x0E000000,
    MMU_AREA_END_SRAM = 0x0E00FFFF,
    MMU_AREA_SIZE_SRAM = MMU_AREA_END_SRAM - MMU_AREA_BASE_SRAM
};

# define MEMORY_SIZE 0x10000000

struct memory
{
    union {
        struct {
            // General Internal Memory
            uint8_t bios[0x00004000];
            uint8_t _reserved1[0x1ffc000];
            uint8_t on_board_wram[0x40000];
            uint8_t _reserved2[0xfc0000];
            uint8_t on_chip_wram[0x8000];
            uint8_t _reserved3[0xff8000];
            uint8_t ioreg[0x400];
            uint8_t _reserved4[0xfffc00];

            // Internal Display Memory
            uint8_t pram[0x400];
            uint8_t _reserved5[0xfffc00];
            uint8_t vram[0x18000];
            uint8_t _reserved6[0xfe8000];
            uint8_t oam[0x400];
            uint8_t _reserved7[0xfffc00];

            // External Memory (Game Pak)
            uint8_t external_rom_0[0x2000000];
            uint8_t external_rom_1[0x2000000];
            uint8_t external_rom_2[0x2000000];
            uint8_t external_sram[0x10000];
            uint8_t _reserved8[0x1ff0000];
        };
        uint8_t raw[MEMORY_SIZE];
    };
} __packed;

static_assert(sizeof(struct memory) == MEMORY_SIZE);

uint8_t mmu_read8(uint32_t addr);
uint16_t mmu_read16(uint32_t addr);
uint32_t mmu_read32(uint32_t addr);
void mmu_write8(uint32_t addr, uint8_t val);
void mmu_write16(uint32_t addr, uint16_t val);
void mmu_write32(uint32_t addr, uint32_t val);
void *mmu_load_addr(uint32_t shift);
void mmu_lock(void);
void mmu_unlock(void);

bool mmu_load_rom(char const *path);

static inline int __mmu_cond_lock__(void)
{
    mmu_lock();
    return (0);
}

static inline int __mmu_cond_unlock__(void)
{
    mmu_unlock();
    return (0);
}

/**
 * Use a safe memory expression in conditionnal ex
 */
# define mmu_safe_check(expr)                  \
    !__mmu_cond_lock__() &&                    \
    (                                          \
        (expr && !__mmu_cond_unlock__())       \
        ||                                     \
        (!expr && __mmu_cond_unlock__() != 0)  \
    )

/**
 * Use a safe memory expression
 */
# define mmu_safe_expr(expr)    \
    mmu_lock();                 \
    expr;                       \
    mmu_unlock();

#endif /* _MMU_MMU_H_ */