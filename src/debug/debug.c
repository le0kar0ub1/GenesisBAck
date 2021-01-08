/******************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include "debug/debug.h"
# include "modules/module.h"

const struct command commands[] =
{
    {
        .name = "quit",
        .minimal = "q",
        .minargs = 0,
        .maxargs = 0,
        .help = "quit",
        .description = "Quit the program",
        .handler = debug_cmd_quit
    },
    {
        .name = "help",
        .minimal = "h",
        .minargs = 0,
        .maxargs = 1,
        .help = "help [CMD]",
        .description = "Display help for all commands or the CMD",
        .handler = debug_cmd_help
    },
    {
        .name = "continue",
        .minimal = "c",
        .minargs = 0,
        .maxargs = 0,
        .help = "continue",
        .description = "Execute until next breakpoint",
        .handler = debug_cmd_continue
    },
    {
        .name = "next",
        .minimal = "n",
        .minargs = 0,
        .maxargs = 1,
        .help = "next [N]",
        .description = "Execute the next next N instruction, defaulting to 1",
        .handler = debug_cmd_next
    },
    {
        .name = "dump",
        .minimal = NULL,
        .minargs = 2,
        .maxargs = 2,
        .help = "dump SIZE ADDRESS",
        .description = "Hexdump SIZE bytes starting at the given ADDRESS",
        .handler = debug_cmd_dump
    },
    {
        .name = "regs",
        .minimal = "r",
        .minargs = 0,
        .maxargs = 1,
        .help = "regs [REG]",
        .description = "Display all the registers or the REG",
        .handler = debug_cmd_regs
    },
    {
        .name = "burst",
        .minimal = "b",
        .minargs = 0,
        .maxargs = 2,
        .help = "burst [{(N)|(N ADDR)]",
        .description = "Disassemble N instructions at the given address, defaulting to PC",
        .handler = debug_cmd_burst
    },
    {
        .name = "breakpoint",
        .minimal = "br",
        .minargs = 1,
        .maxargs = 1,
        .help = "breakpoint ADDR",
        .description = "Put a breakpoint at the given address",
        .handler = debug_cmd_breakpoint
    },
    {
        .name = "wreg",
        .minimal = NULL,
        .minargs = 2,
        .maxargs = 2,
        .help = "wreg REG EXPR",
        .description = "Write the EXPR in the REG",
        .handler = debug_cmd_wreg
    },
    {
        .name = "load",
        .minimal = NULL,
        .minargs = 1,
        .maxargs = 2,
        .help = "load [SIZE] ADDR",
        .description = "Print SIZE of the given address, defaulting to 4",
        .handler = debug_cmd_load
    },
    {
        .name = "module",
        .minimal = "mod",
        .minargs = 1,
        .maxargs = 1,
        .help = "module [NAME|list]",
        .description = "Display information about the given module or *list* them",
        .handler = debug_cmd_module
    },
    {
        .name = NULL,
        .minimal = NULL,
        .minargs = 0,
        .maxargs = 0,
        .help = NULL,
        .description = NULL,
        .handler = NULL
    }
};

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

static void debug_start(void)
{
    char *input;
    size_t args;
    char **cmd;

    while ((input = readline("$> ")) != NULL)
    {
        cmd = strtotab(input, &args);
        if (args == 0)
            continue;
        if ((!strcmp("quit", cmd[0]) || !strcmp("q", cmd[0])) && args == 1)
                return;
        for (int i = 0; commands[i].name; i++)
        {
            if (
                (
                    !strcmp(commands[i].name, cmd[0])   ||
                    (
                        commands[i].minimal &&
                        !strcmp(commands[i].minimal, cmd[0])
                    )
                ) &&
                (
                    args >= commands[i].minargs + 1 &&
                    args <= commands[i].maxargs + 1
                )
            )
                commands[i].handler(args, (char const **)cmd);
        }
        free(cmd);
        free(input);
    }
}

static void debug_init(void) {}

static void debug_exit(void) {}

static void debug_reset(void) {}

REGISTER_MODULE(
    debug,
    "A GDB like debugger which schedule the DEBUG execution, using the core",
    MODULE_HOOK_CORE,
    debug_init,
    debug_exit,
    debug_reset,
    debug_start,
    NULL,
    NULL
);