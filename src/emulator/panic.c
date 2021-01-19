/******************************************************************************
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include <genesisback.h>
# include <debug/debug.h>
# include <modules/exithooks.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>

/**
 * \brief Back to basic, panic function
 *
 * Inspired by kernel development, no return from here
 *
 * TODO: A reset for the machine and/or a dump debug
 */
void __noreturn _panic(char const *anywhere, char const *fmt, ...)
{
    printf("[%s%s%s](%spanicked%s): ", ANSI_RED, anywhere, ANSI_RESET, ANSI_RED, ANSI_RESET);
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    printf("\n");
    #if ROUTINE == ROUTINE_DEBUG
        debug_cmd_regs(1, NULL);
    #endif

    exithooks_run_allhooks();

    exit(1);
}