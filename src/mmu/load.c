/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "modules/module.h"
# include "mmu/mmu.h"
# include "gba/cartridge.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

/**
 * Load the given rom in the good memory area
 * Currently not using waitstate, but a copy is put in all roms 
 */
bool mmu_load_rom(char const *path)
{
    int fd;
    
    if (!path) {
        LOG_ERR("Invalid rom path");
        return (false);
    }
    fd = open(path, O_RDONLY);
    if (fd == -1) {
        LOG_ERR("Invalid rom path");
        return (false);
    }
    if (!module_is_initialized_runmod("mmu")) {
        LOG_ERR("Memory uninitialized");
        return (false);
    }
    read(fd, (void *)mmu_load_addr(MMU_AREA_BASE_ROM0), MMU_AREA_SIZE_ROM0);
    lseek(fd, 0, SEEK_SET);
    read(fd, (void *)mmu_load_addr(MMU_AREA_BASE_ROM1), MMU_AREA_SIZE_ROM1);
    lseek(fd, 0, SEEK_SET);
    read(fd, (void *)mmu_load_addr(MMU_AREA_BASE_ROM2), MMU_AREA_SIZE_ROM2);
    if (!cartridge_check_header()) {
        LOG_ERR("GBA cartridge header check failed");
        return (false);
    }
    return (true);
}