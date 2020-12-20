/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <stdint.h>

// BIOS ROM     16 KBytes
// Work RAM     288 KBytes (Fast 32K on-chip, plus Slow 256K on-board)
// VRAM         96 KBytes
// OAM          1 KByte (128 OBJs 3x16bit, 32 OBJ-Rotation/Scalings 4x16bit)
// Palette RAM  1 KByte (256 BG colors, 256 OBJ colors)

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
        uint8_t raw[0x10000000];
    };
} __packed;