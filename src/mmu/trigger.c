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

static pthread_t thread;
static bool kill_thread = false;

static uint32_t *trigger_range = NULL;

/**
 * Limit ourself to this range for the MMU checkup
 * else we will clobber the perfs
 * eh ? I heard hardcode in the bottom right
 */
# define MMU_TRIGGER_MIN_ADDR 0x4000000
# define MMU_TRIGGER_MAX_ADDR 0x40003FE

static void mmu_trigger_init(void)
{
    struct mmu_trigger *mm;
    uint32_t min;
    uint32_t max;

    mm = (struct mmu_trigger *)__start_mmutriggers;
    min = mm->start;
    max = mm->end;
    trigger_range = malloc(2 * 4); // currently hardcoded one range only in the IO reg map
    while ((uintptr_t)mm < (uintptr_t)__stop_mmutriggers) {
        if (min > mm->start) {
            min = mm->start;
        }
        if (max < mm->end) {
            max = mm->end;
        }
        mm++;
    }
    if (min < MMU_TRIGGER_MIN_ADDR || max > MMU_TRIGGER_MAX_ADDR)
        panic("MMU trigger invalid range %#x - %#x", min, max);
    trigger_range[0] = min;
    trigger_range[1] = max;
}

static void mmu_trigger_exit(void)
{
    kill_thread = true;
    pthread_join(thread, NULL);
    free(trigger_range);
}

static void mmu_trigger_reset(void)
{
    mmu_trigger_init();
}

void *mmu_trigger_thread(void *arg)
{
    uint32_t val = (uint32_t)(uint64_t)arg;
    uint32_t addr = ((uint32_t)((uint64_t)arg >> 32ul)) & 0xFFFFFFF;
    uint32_t size = (uint32_t)(((uint64_t)arg) >> 60ul);

    return (NULL);
}

void mmu_trigger_handle_write(uint32_t addr, uint32_t size, uint32_t val)
{
    if (addr > trigger_range[0] && addr < trigger_range[1]) {
        uint64_t pushme = (
            (uint64_t)val | 
            ((uint64_t)addr << 32ul) |
            (((uint64_t)size / 8) << 60ul)
        );
        if (pthread_create(&thread, NULL, mmu_trigger_thread, (void *)pushme) != 0)
            panic("Thread creation failed");
    }
}

static void mmu_trigger_info(void)
{
    struct mmu_trigger *mm = (struct mmu_trigger *)__start_mmutriggers;

    while ((uintptr_t)mm < (uintptr_t)__stop_mmutriggers) {
        printf("[%s] %#x - %#x\n", mm->name, mm->start, mm->end);
        mm++;
    }
}

REGISTER_MODULE(
    mmu_trigger,
    "Module which handle the memory trigger of the GBA components",
    MODULE_HOOK_LAST,
    mmu_trigger_init,
    mmu_trigger_exit,
    mmu_trigger_exit,
    NULL,
    NULL,
    mmu_trigger_info
);