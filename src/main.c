/******************************************************************************
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include "genesisback.h"
# include "mmu/mmu.h"
# include "core/core.h"
# include <stdlib.h>
# include "init/inithooks.h"

char const *rom = NULL; 

/**
 * Program entry point
 * Obviously the emulator take the flow firstly to initialize the targeted machine
 */
int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("USAGE:\n");
		printf("    ./%s path_to_rom\n", argv[0]);
		return (EXIT_FAILURE);
	} else {
		rom = argv[1];
	}
	run_inithooks_bylevel();

	core_start();

	core_exit();
	mmu_exit();
	return (0);
}
