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
# include <mmu/mmu.h>

/**
 * Register a range of address
 * If write in this range the given thread (condition) will be triggered
 */
struct mmu_trigger
{
    const char name[16];
    const uint32_t start;
    const uint32_t end;
    bool (* const shouldistart)(uint32_t addr, uint32_t size);
    const pthread_mutex_t *mutex;
    const pthread_cond_t  *threadup;
};

# define REGISTER_MMU_TRIGGER(xname, xstart, xend, xshouldistart, xmutex, xthreadup)           \
    __attribute__((__used__, __aligned__(8), __section__("mmutriggers")))                      \
    static const struct mmu_trigger xname = {                                                  \
        .name         = #xname,                                                                \
        .start        = xstart,                                                                \
        .end          = xend,                                                                  \
        .shouldistart = xshouldistart,                                                         \
        .mutex        = xmutex,                                                                \
        .threadup     = xthreadup                                                              \
    };


#endif /* _MMU_TRIGGER_H_ */