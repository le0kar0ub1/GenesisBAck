/******************************************************************************
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include "genesisback.h"
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
void __noreturn panic(char const *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    exit(0);
}