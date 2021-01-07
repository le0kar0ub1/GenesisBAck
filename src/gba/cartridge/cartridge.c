/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "mmu/mmu.h"
# include "gba/cartridge.h"

static uint8_t cartridge_nintendo_logo_bitmap[156] = {
                        0x24, 0xff, 0xae, 0x51, 0x69, 0x9a, 0xa2, 0x21, 0x3d, 0x84, 0x82, 0x0a,
0x84, 0xe4, 0x09, 0xad, 0x11, 0x24, 0x8b, 0x98, 0xc0, 0x81, 0x7f, 0x21, 0xa3, 0x52, 0xbe, 0x19,
0x93, 0x09, 0xce, 0x20, 0x10, 0x46, 0x4a, 0x4a, 0xf8, 0x27, 0x31, 0xec, 0x58, 0xc7, 0xe8, 0x33,
0x82, 0xe3, 0xce, 0xbf, 0x85, 0xf4, 0xdf, 0x94, 0xce, 0x4b, 0x09, 0xc1, 0x94, 0x56, 0x8a, 0xc0,
0x13, 0x72, 0xa7, 0xfc, 0x9f, 0x84, 0x4d, 0x73, 0xa3, 0xca, 0x9a, 0x61, 0x58, 0x97, 0xa3, 0x27,
0xfc, 0x03, 0x98, 0x76, 0x23, 0x1d, 0xc7, 0x61, 0x03, 0x04, 0xae, 0x56, 0xbf, 0x38, 0x84, 0x00,
0x40, 0xa7, 0x0e, 0xfd, 0xff, 0x52, 0xfe, 0x03, 0x6f, 0x95, 0x30, 0xf1, 0x97, 0xfb, 0xc0, 0x85,
0x60, 0xd6, 0x80, 0x25, 0xa9, 0x63, 0xbe, 0x03, 0x01, 0x4e, 0x38, 0xe2, 0xf9, 0xa2, 0x34, 0xff,
0xbb, 0x3e, 0x03, 0x44, 0x78, 0x00, 0x90, 0xcb, 0x88, 0x11, 0x3a, 0x94, 0x65, 0xc0, 0x7c, 0x63,
0x87, 0xf0, 0x3c, 0xaf, 0xd6, 0x25, 0xe4, 0x8b, 0x38, 0x0a, 0xac, 0x72, 0x21, 0xd4, 0xf8, 0x07,
};

static bool cartridge_checksum(void)
{
    uint32_t shift = 0xA0;
    int32_t check = 0;

    while (shift <= 0xBC) {
        check -= mmu_read8(MMU_AREA_BASE_ROM0 + shift);
        shift++;
    }
    check = (check - 0x19) & 0xFF;
    if (check != mmu_read8(MMU_AREA_BASE_ROM0 + 0xBD))
        return (false);
    return (true);
}

static bool cartridge_nintendo_logo_check(void)
{
    struct cartridge_header *hdr = (struct cartridge_header *)mmu_load_addr(MMU_AREA_BASE_ROM0);
    uint32_t i = 0;    

    while (i < sizeof(cartridge_nintendo_logo_bitmap)) {
        if (hdr->nintendo_logo[i] != cartridge_nintendo_logo_bitmap[i])
            return (false);
        i++;
    }
    return (true);
}

uint32_t cartridge_get_entry_point(void)
{
    struct cartridge_header *hdr = (struct cartridge_header *)mmu_load_addr(MMU_AREA_BASE_ROM0);

    if (hdr->boot_mode == 0x1) { // joybus
        return (CARTRIDGE_HEADER_JOY_ENTRY);
    } else if (hdr->boot_mode == 0x2 || hdr->boot_mode == 0x3) { // Normal / multiplay
        return (CARTRIDGE_HEADER_RAM_ENTRY);
    } else if (hdr->boot_mode == 0x0){ // basic entry
        return (CARTRIDGE_HEADER_ROM_ENTRY);
    } else {
        panic("Invalid boot mode %u", hdr->boot_mode);
    }
}

char const *cartridge_get_game_title(void)
{
    struct cartridge_header *hdr = (struct cartridge_header *)mmu_load_addr(MMU_AREA_BASE_ROM0);

    return ((char const *)&(hdr->game_title));
}

bool cartridge_check_header(void)
{
    struct cartridge_header *hdr = (struct cartridge_header *)mmu_load_addr(MMU_AREA_BASE_ROM0);

    if (hdr->v96h != 0x96) {
        LOG_ERR("Cartidge 96h isn't 96h");
        return (false);
    }
    if (!cartridge_checksum()) {
        LOG_ERR("Cartridge checksum failed");
        return (false);
    }
    if (!cartridge_nintendo_logo_check()) {
        LOG_ERR("Cartridge nintendo logo invalid");
        return (false);
    }
    // if (hdr->boot_mode) // unhandled boot mode != 0
        // panic("Unhandled boot mode");
    return (true);
}