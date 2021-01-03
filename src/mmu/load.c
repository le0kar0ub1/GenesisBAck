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
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

/**
 * Load the given rom in the good memory area
 * Currently make a copy in all slots 
 */
bool mmu_load_rom(char const *path)
{
    int fd;
    
    if (!path) {
        LOG_ERR("Invalid rom path");
        return (false);
    }
    fd = open(path, O_RDONLY);
    if (!fd) {
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
    return (true);
}