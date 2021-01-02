/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _DEF_MODULE_H_
# define _DEF_MODULE_H_

# include "def/def.h"

enum MODULE_HOOKS {
    MODULE_HOOK_BOOTSTRAP = 0,
    MODULE_HOOK_CORE = 1,
    MODULE_HOOK_SOC = 2,
    MODULE_HOOK_LAST = 3,
    MODULE_HOOK_MAX = 3
};

struct module
{
    char name[16];
    char desc[128];
    enum MODULE_HOOKS hook;
    bool initialized;
    void (*init)(void);
    void (*exit)(void);
    void (*reset)(void);
    void (*handler)(void);
    void (*info)(void);
};

# define REGISTER_MODULE(xname, xdesc, xhook, xinit, xexit, xreset, xhandler, xinfo)    \
    __attribute__((__used__, __aligned__(8), __section__("genesisbackmodule")))         \
    static struct module xname = {                                                      \
        .name    = #xname,                                                              \
        .desc    = xdesc,                                                               \
        .hook    = xhook,                                                               \
        .initialized = false,                                                           \
        .init    = xinit,                                                               \
        .exit    = xexit,                                                               \
        .reset   = xreset,                                                              \
        .handler = xhandler,                                                            \
        .info    = xinfo                                                                \
    };

void module_init_runmod(char const *name);
void module_init_runhook(enum MODULE_HOOKS hook);

void module_exit_runmod(char const *name);
void module_exit_runhook(enum MODULE_HOOKS hook);

void module_reset_runmod(char const *name);
void module_reset_runhook(enum MODULE_HOOKS hook);

void module_handler_runmod(char const *name);

#endif /* !_DEF_MODULE_H_ */