/******************************************************************************
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include "debug/debug.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>

const struct command commands[] =
{
    {
        .name = "quit",
        .minargs = 0,
        .maxargs = 0,
        .help = "quit",
        .description = "Quit the program",
        .handler = debug_cmd_quit
    },
    {
        .name = "help",
        .minargs = 0,
        .maxargs = 1,
        .help = "help [CMD]",
        .description = "Display help for all commands or the CMD",
        .handler = debug_cmd_help
    },
    {
        .name = "continue",
        .minargs = 0,
        .maxargs = 0,
        .help = "continue",
        .description = "Execute until next breakpoint",
        .handler = debug_cmd_continue
    },
    {
        .name = "next",
        .minargs = 0,
        .maxargs = 1,
        .help = "next [N]",
        .description = "Execute the next next N instruction, defaulting to 1",
        .handler = debug_cmd_next
    },
    {
        .name = "dump",
        .minargs = 2,
        .maxargs = 2,
        .help = "dump SIZE ADDRESS",
        .description = "Dump size bytes of the given address",
        .handler = debug_cmd_dump
    },
    {
        .name = "regs",
        .minargs = 0,
        .maxargs = 1,
        .help = "regs [R]",
        .description = "Display all the registers or the register R",
        .handler = debug_cmd_regs
    },
    {
        .name = "burst",
        .minargs = 0,
        .maxargs = 1,
        .help = "burst [ADDR]",
        .description = "disassemble the given address, defaulting to PC",
        .handler = debug_cmd_burst
    },
    {
        .name = "brk",
        .minargs = 1,
        .maxargs = 1,
        .help = "brk ADDR",
        .description = "Put a breakpoint at the given address",
        .handler = debug_cmd_breakpoint
    },
    {
        .name = NULL,
        .minargs = 0,
        .maxargs = 0,
        .help = NULL,
        .description = NULL,
        .handler = NULL
    }
};

void debug_init(void) {}

void debug_exit(void) {}

int get_command_descriptor_index(char const *name)
{
    int i = 0;
    
    while (commands[i].name) {
        if (!strcmp(commands[i].name, name))
            return (i);
        i++;
    }
    return (-1);
}

# define IS_SPACE(x) (x == '\t' || x == ' ')

static char **strtotab(char *input, size_t *len)
{
    char **tab;
    size_t size;
    size_t i, j;
    bool last_was_space = true;

    *len = 0;
    i = 0;
    while (input[i]) {
        if (!last_was_space && IS_SPACE(input[i])) {
            last_was_space = true;
        } else if (last_was_space && !IS_SPACE(input[i])) {
            last_was_space = false;
            (*len) += 1;
        }
        i++;
    }

    tab = malloc(sizeof(void *) * (*len + 1));
    i = 0;
    j = 0;
    last_was_space = true;
    while (input[i]) {
        if (!last_was_space && IS_SPACE(input[i])) {
            last_was_space = true;
            input[i] = 0;
        } else if (last_was_space && !IS_SPACE(input[i])) {
            last_was_space = false;
            tab[j] = &input[i];
            j++;
        }
        i++;
    }
    tab[j] = NULL;
    return (tab);
}

#undef IS_SPACE

void debug_start(void)
{
    char *input;
    size_t args;
    char **cmd;

    while ((input = readline("$> ")) != NULL)
    {
        cmd = strtotab(input, &args);
        if (args == 0)
            continue;
        for (int i = 0; commands[i].name; i++)
        {
            if (
                !strcmp(commands[i].name, cmd[0]) &&
                args >= commands[i].minargs + 1 &&
                args <= commands[i].maxargs + 1
            )
                commands[i].handler(args, (char const **)cmd);
        }
        free(cmd);
        free(input);
    }
}