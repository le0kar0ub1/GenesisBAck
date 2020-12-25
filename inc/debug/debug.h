/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _DEBUG_DEBUG_H_
# define _DEBUG_DEBUG_H_

# include "genesisback.h"

struct command
{
    char const *name;
    uint32_t minargs;
    uint32_t maxargs;
    char const *help;
    char const *description;
    void (*handler)(int, char const **);
};

void debug_init(void);
void debug_exit(void);
void debug_start(void);
int get_command_descriptor_index(char const *name);

void debug_cmd_quit(int ac, char const **av);
void debug_cmd_help(int ac, char const **av);
void debug_cmd_continue(int ac, char const **av);
void debug_cmd_next(int ac, char const **av);
void debug_cmd_dump(int ac, char const **av);
void debug_cmd_regs(int ac, char const **av);
void debug_cmd_burst(int ac, char const **av);
void debug_cmd_breakpoint(int ac, char const **av);


#endif /* _DEBUG_DEBUG_H_ */