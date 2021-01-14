/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <mmu/trigger.h>
# include <modules/module.h>
# include <stdlib.h>
# include <pthread.h>

extern struct mmu_trigger __start_mmutriggers[];
extern struct mmu_trigger __stop_mmutriggers[];

static bool kill_thread = false;

static uint32_t *trigger_range = NULL;

/**
 * Limit ourself to this range for the MMU checkup
 * else we will clobber the perfs
 * eh ? I heard hardcode in the bottom right
 */
# define MMU_TRIGGER_MIN_ADDR 0x4000000
# define MMU_TRIGGER_MAX_ADDR 0x40003FE

static void *mmu_trigger_thread(void *arg)
{
    struct mmu_trigger *mm = (struct mmu_trigger *)__start_mmutriggers;
    struct mmhit hit = *((struct mmhit *)&arg);
 
    while ((uintptr_t)mm < (uintptr_t)__stop_mmutriggers && !kill_thread) {
        if (mm->start <= hit.addr && mm->end >= (hit.addr + (uint32_t)hit.size)) {
            if (mm->exec && mm->module->initialized) {
                if (!mm->check || (mm->check && mm->check(hit))) {
                    printf("trigger %s\n", mm->module->name);
                    pthread_mutex_lock(&mm->mutex);
                    mm->count++;
                    mm->running = true;
                    mm->exec(hit);
                    mm->running = false;
                    pthread_mutex_unlock(&mm->mutex);
                }
            }
            break;
        }
        mm++;
    }
    return (NULL);
}

void mmu_trigger_handle_write(uint32_t addr, uint32_t size, uint32_t val)
{
    if (trigger_range && addr > trigger_range[0] && addr < trigger_range[1]) {
        struct mmhit hit = {
            .val = val,
            .addr = addr & 0xFFFFFFF,
            .size = size
        };
        pthread_t thread;
        if (pthread_create(&thread, NULL, mmu_trigger_thread, (void *)hit.raw) != 0) {
            panic("Thread creation failed");
        }
    }
}

static void mmu_trigger_init(void)
{
    struct mmu_trigger *mm;
    uint32_t min;
    uint32_t max;

    mm = (struct mmu_trigger *)__start_mmutriggers;
    min = mm->start;
    max = mm->end;
    trigger_range = malloc(2 * 4); // currently hardcoded one range only in the IO reg map
    if (!trigger_range) {
        panic("Allocation failed");
    }
    while ((uintptr_t)mm < (uintptr_t)__stop_mmutriggers) {
        if (min > mm->start) {
            min = mm->start;
        }
        if (max < mm->end) {
            max = mm->end;
        }
        mm++;
    }
    if (min < MMU_TRIGGER_MIN_ADDR || max > MMU_TRIGGER_MAX_ADDR) {
        panic("MMU trigger invalid range %#x - %#x", min, max);
    }
    trigger_range[0] = min;
    trigger_range[1] = max;
}

static void mmu_trigger_info(void)
{
    struct mmu_trigger *mm = (struct mmu_trigger *)__start_mmutriggers;

    while ((uintptr_t)mm < (uintptr_t)__stop_mmutriggers) {
        printf(
            "%-16s %s   %#08x - %#08x\n",
            mm->module->name,
            mm->running ? "[run]    " : "[stopped]",
            mm->start,
            mm->end
        );
        mm++;
    }
}

static void mmu_trigger_exit(void)
{
    kill_thread = true;
    free(trigger_range);
}

static void mmu_trigger_reset(void)
{
    mmu_trigger_init();
}

REGISTER_MODULE(
    mmu_trigger,
    "Module which handle the memory trigger of the GBA components",
    MODULE_HOOK_LAST,
    mmu_trigger_init,
    mmu_trigger_exit,
    mmu_trigger_reset,
    NULL,
    NULL,
    mmu_trigger_info
);