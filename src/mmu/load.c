/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "mmu/mmu.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

extern struct memory *mem;

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
    if (!mem) {
        LOG_ERR("Memory uninitilalized");
        return (false);
    }
    read(fd, &(mem->external_rom_0), 0x2000000);
    // lseek(fd, 0, SEEK_SET);
    // read(fd, &(mem->external_rom_1), 0x2000000);
    // lseek(fd, 0, SEEK_SET);
    // read(fd, &(mem->external_rom_2), 0x2000000);
    return (true);
}