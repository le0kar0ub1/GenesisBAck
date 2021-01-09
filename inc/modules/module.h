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
    MODULE_HOOK_GBA = 2,
    MODULE_HOOK_LAST = 3,
    MODULE_HOOK_MAX = 3
};

#ifndef CONFIG_INITLEVEL
    # define CONFIG_INITLEVEL 3
#endif

struct module
{
    char const name[32];
    char const desc[128];
    enum MODULE_HOOKS const hook;
    bool initialized;
    bool running;
    void (* const init)(void);
    void (* const exit)(void);
    void (* const reset)(void);
    void (* const start)(void);
    void (* const stop)(void);
    void (* const info)(void);
};

/**
 * Except for the CORE and the DEBUG module which are owned by CORE hook
 * Assuming that if you register a start & stop function, the module is threaded
 */
# define REGISTER_MODULE(xname, xdesc, xhook, xinit, xexit, xreset, xstart, xstop, xinfo)  \
    __attribute__((__used__, __aligned__(8), __section__("genesisbackmodules")))           \
    static const struct module xname = {                                                   \
        .name    = #xname,                                                                 \
        .desc    = xdesc,                                                                  \
        .hook    = xhook,                                                                  \
        .initialized = false,                                                              \
        .running     = false,                                                              \
        .init    = xinit,                                                                  \
        .exit    = xexit,                                                                  \
        .reset   = xreset,                                                                 \
        .start   = xstart,                                                                 \
        .stop    = xstop,                                                                  \
        .info    = xinfo                                                                   \
    };

void module_init_runmod(char const *name);
void module_init_runhook(enum MODULE_HOOKS hook);

void module_exit_runmod(char const *name);
void module_exit_runhook(enum MODULE_HOOKS hook);

void module_reset_runmod(char const *name);
void module_reset_runhook(enum MODULE_HOOKS hook);

void module_start_runmod(char const *name);
void module_start_runhook(enum MODULE_HOOKS hook);

void module_stop_runmod(char const *name);
void module_stop_runhook(enum MODULE_HOOKS hook);

void module_info_runmod(char const *name);

bool module_is_initialized_runmod(char const *name);
bool module_is_running_runmod(char const *name);

struct module *module_request_mod(char const *name);

#endif /* !_DEF_MODULE_H_ */