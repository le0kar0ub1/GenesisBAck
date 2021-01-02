/******************************************************************************
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include <stdlib.h>

# include "genesisback.h"
# include "mmu/mmu.h"
# include "core/core.h"
# include "debug/debug.h"
# include "modules/inithooks.h"
# include "modules/exithooks.h"

char const *rom = NULL; 

/**
 * Program entry point
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
	/**
	 * Run all the modules init calls by levels from start
	 */
	inithooks_run_allhooks();

#if ROUTINE == ROUTINE_RELEASE
	module_handler_runmod("core");
#elif ROUTINE == ROUTINE_DEBUG
	module_handler_runmod("debug");
#else
	#error
#endif
	/**
	 * Run all the modules exit calls by levels from latest
	 */
	exithooks_run_allhooks();
	return (0);
}
