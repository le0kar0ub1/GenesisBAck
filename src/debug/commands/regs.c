/******************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\*****************************************************************************/

# include "debug/debug.h"
# include "core/core.h"

static inline char const *get_opmode(uint32_t opmode)
{
    switch (opmode)
    {
        case OPERATION_MODE_USER:
            return ("User");
        case OPERATION_MODE_FIQ:
            return ("FIQ");
        case OPERATION_MODE_IRQ:
            return ("IRQ");
        case OPERATION_MODE_SUPERVISOR:
            return ("Supervisor");
        case OPERATION_MODE_ABORT:
            return ("Abort");
        case OPERATION_MODE_UNDEFINED:
            return ("Undefined");
        case OPERATION_MODE_SYSTEM:
            return ("System");
        default:
            return ("Unknow");
    }
}

static inline char const *get_state(uint32_t state)
{
    switch (state)
    {
        case STATE_ARM:
            return ("ARM");
        case STATE_THUMB:
            return ("THUMB");
        default:
            return ("Unknow");
    }
}

static inline void display_psr_regs(struct register_psr psr)
{
    // printf("    opmode: %s\n", get_opmode(psr.opmode));
    // printf("     state: %s\n", get_state(psr.state));
    // printf("   fiq/irq: %u/%u\n", psr.fiq_disable, psr.irq_disable);
    // printf("  overflow: %u\n", psr.overflow);
    // printf("     carry: %u\n", psr.carry);
    // printf("      zero: %u\n", psr.zero);
    // printf("  negative: %u\n", psr.negative);
    printf("  fiq: %u | overflow: %u |     zero: %u | opmode: %s\n", psr.fiq_disable, psr.overflow, psr.zero, get_opmode(psr.opmode));
    printf("  irq: %u |    carry: %u | negative: %u |  state: %s\n", psr.irq_disable, psr.carry, psr.negative, get_state(psr.state));
}

void debug_cmd_regs(int ac, char const **av)
{
    struct opmode_regs *regs = core_get_context_regs();

    if (ac == 2) {

    } else if (ac == 1) {
        printf(" r0: %08x |  r1: %08x |  r2: %08x |  r3: %08x\n", *(regs->raw[0]), *(regs->raw[1]), *(regs->raw[2]), *(regs->raw[3]));
        printf(" r4: %08x |  r5: %08x |  r6: %08x |  r7: %08x\n", *(regs->raw[4]), *(regs->raw[5]), *(regs->raw[6]), *(regs->raw[7]));
        printf(" r8: %08x |  r9: %08x | r10: %08x | r11: %08x\n", *(regs->raw[8]), *(regs->raw[9]), *(regs->raw[10]), *(regs->raw[11]));
        printf("r12: %08x | r13: %08x | r14: %08x | r15: %08x\n", *(regs->raw[12]), *(regs->raw[13]), *(regs->raw[14]), *(regs->raw[15]));
        printf("\n");
        display_psr_regs(*(regs->cpsr));
        // if (regs->spsr) {
        //     printf("spsr:\n");
        //     display_psr_reg(*(regs->spsr));
        // } else {
        //     printf("spsr: None\n");
        // }
        // printf("prefetch: %08x\n", core_read_prefetch());
    }
}