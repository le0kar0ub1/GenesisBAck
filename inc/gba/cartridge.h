/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _MMU_CARTRIDGE_H_
# define _MMU_CARTRIDGE_H_

# include <genesisback.h>
# include <mmu/mmu.h>

# define CARTRIDGE_HEADER_ROM_ENTRY (MMU_AREA_BASE_ROM0 + 0x00)
# define CARTRIDGE_HEADER_RAM_ENTRY (MMU_AREA_BASE_ROM0 + 0xC0)
# define CARTRIDGE_HEADER_JOY_ENTRY (MMU_AREA_BASE_ROM0 + 0xE0)

struct cartridge_header
{
    uint32_t rom_entry; /* (32bit ARM branch opcode, eg. "B rom_start") */
    uint8_t nintendo_logo[156]; /* (compressed bitmap, required!) */
    char game_title[12]; /* (uppercase ascii, max 12 characters) */
    char game_code[4]; /* (uppercase ascii, 4 characters) */
    char maker_code[2]; /* (uppercase ascii, 2 characters) */
    uint8_t v96h; /* (must be 96h, required!) */
    uint8_t main_unit_code; /* (00h for current GBA models) */
    uint8_t dev_type; /* (usually 00h) (bit7=DACS/debug related) */
    uint8_t _reserved1[7]; /* (should be zero filled) */
    uint8_t software_version; /* (usually 00h) */
    int8_t checksum; /* (header checksum, required!) */
    uint8_t _reserved2[2]; /* (should be zero filled) */
    uint32_t ram_entry; /* (32bit ARM branch opcode, eg. "B ram_start") */
    uint8_t boot_mode; /* (init as 00h - BIOS overwrites this value!) */
    uint8_t slave_id; /* (init as 00h - BIOS overwrites this value!) */
    uint8_t _reserved3[26]; /*(seems to be unused) */
    uint32_t joy_entry; /* (32bit ARM branch opcode, eg. "B joy_start") */
};

bool cartridge_check_header(void);
uint32_t cartridge_get_entry_point(void);
char const *cartridge_get_game_title(void);

#endif /* !_MMU_CARTRIDGE_H_ */