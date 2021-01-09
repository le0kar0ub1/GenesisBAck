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
# include <stdlib.h>
# include <string.h>

struct command
{
    char const *name;
    char const *minimal;
    uint32_t minargs;
    uint32_t maxargs;
    char const *help;
    char const *description;
    void (*handler)(int, char const **);
};

int get_command_descriptor_index(char const *name);

int32_t breakpoint_get_and_remove(void);

void debug_cmd_quit(int ac, char const **av);
void debug_cmd_help(int ac, char const **av);
void debug_cmd_continue(int ac, char const **av);
void debug_cmd_next(int ac, char const **av);
void debug_cmd_dump(int ac, char const **av);
void debug_cmd_regs(int ac, char const **av);
void debug_cmd_burst(int ac, char const **av);
void debug_cmd_breakpoint(int ac, char const **av);
void debug_cmd_wreg(int ac, char const **av);
void debug_cmd_load(int ac, char const **av);
void debug_cmd_store(int ac, char const **av);
void debug_cmd_module(int ac, char const **av);

static inline int get_base(char const *inp)
{
    if (strlen(inp) < 3)
        return (10);
    if (!strncmp(inp, "0x", 2) || !strncmp(inp, "0X", 2))
        return (16);
    if (!strncmp(inp, "0b", 2) || !strncmp(inp, "0B", 2))
        return (2);
    if (!strncmp(inp, "0o", 2) || !strncmp(inp, "0O", 2))
        return (8);
    return (10);
}

static inline int32_t get_reg(char const *s)
{
    if (strlen(s) < 2)
        return (-1);
    int ret = atoi(s++);
    if (ret > 15)
        return (-1);
    return (ret);
}

#endif /* _DEBUG_DEBUG_H_ */