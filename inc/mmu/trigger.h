/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _MMU_TRIGGER_H_
# define _MMU_TRIGGER_H_

# include <pthread.h>
# include <modules/module.h>
# include <mmu/mmu.h>

struct mmhit
{
    union
    {
        struct
        {
            uint32_t val  : 32;
            uint32_t addr : 28;
            uint32_t size : 4;
        };
        uint64_t raw;
    };
} __packed;

static_assert(sizeof(struct mmhit) == sizeof(uint64_t));

struct mmu_trigger
{
    const struct module *module;
    const uint32_t start;
    const uint32_t end;
    void (* const exec)(struct mmhit hit);
    bool (* const check)(struct mmhit hit);
    pthread_mutex_t mutex;
    bool running;
    volatile size_t wait;
    volatile size_t work;
};

/**
 * Register a range of address
 * If write in this range the given thread (condition) will be triggered
 * The registering MUST be attached to a module
 */
# define REGISTER_MMU_TRIGGER(xmodule, xstart, xend, xcheck, xexec)        \
    __attribute__((__used__, __aligned__(8), __section__("mmutriggers")))  \
    static const struct mmu_trigger xname = {                              \
        .module       = xmodule,                                           \
        .start        = xstart,                                            \
        .end          = xend,                                              \
        .check        = xcheck,                                            \
        .exec         = xexec,                                             \
        .mutex        = PTHREAD_MUTEX_DEFAULT,                             \
        .wait         = 0x0,                                               \
        .work         = 0x0,                                               \
        .running      = false                                              \
    };

void mmu_trigger_handle_write(uint32_t addr, uint32_t size, uint32_t val);

#endif /* _MMU_TRIGGER_H_ */