/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "mmu/mmu.h"
# include "mmu/cartridge.h"

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

uint32_t cartridge_get_entry_point(void)
{
    struct cartridge_header *hdr = (struct cartridge_header *)mmu_load_addr(MMU_AREA_BASE_ROM0);

    if (hdr->boot_mode == 0x1) { // joybus
        return (CARTRIDGE_HEADER_JOY_ENTRY);
    } else if (hdr->boot_mode == 0x2 || hdr->boot_mode == 0x3) { // Normal / multiplay
        return (CARTRIDGE_HEADER_RAM_ENTRY);
    } else { // basic entry
        return (CARTRIDGE_HEADER_ROM_ENTRY);
    }
}

bool cartridge_check_header(void)
{
    struct cartridge_header *hdr = (struct cartridge_header *)mmu_load_addr(MMU_AREA_BASE_ROM0);

    if (hdr->vx96 != 0x96)
        return (false);
    if (!cartridge_checksum())
        return (false);
    // if (hdr->boot_mode) // unhandled boot mode != 0
        // panic("Unhandled boot mode");
    return (true);
}