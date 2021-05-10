/******************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Brian DELALEX
**
\*****************************************************************************/

# include "core/core.h"
# include "debug/debug.h"

void debug_cmd_resume(int ac, char const **av)
{
    core_cpu_restart_exec();
}