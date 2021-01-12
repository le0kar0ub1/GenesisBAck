/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "mmu/trigger.h"
# include <pthread.h>

/*

extern struct mmu_trigger __start_mmutriggers[];
extern struct mmu_trigger __stop_mmutriggers[];

uint64_t mmu_trigger_get_range(void)
{
    struct mmu_trigger *mm;
    uint64_t min;
    uint64_t max;
    
    mm = (struct mmu_trigger *)__start_mmutriggers;
    min = mm->start;
    max = mm->end;
    while ((uintptr_t)mm < (uintptr_t)__stop_mmutriggers) {
        if (min > mm->start) {
            min = mm->start;
        }
        if (max < mm->end) {
            max = mm->end;
        }
        mm++;
    }
    return ((max << 32ul) | min);
}

void *mmu_trigger_handle(void *arg)
{
    uint32_t addr = ((uint32_t *)arg)[0];
    uint32_t size = ((uint32_t *)arg)[1];

    return (NULL);
}

REGISTER_MMU_TRIGGER(
    anything,
    0x0,
    0x0,
    NULL,
    NULL,
    NULL
);

*/