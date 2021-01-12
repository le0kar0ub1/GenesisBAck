/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <core/cycle/exec.h>
# include <core/exceptions.h>
# include <mmu/mmu.h>

static inline uint32_t count_register(uint16_t list)
{
    uint32_t inc = 0;
    uint32_t count = 0;

    while (inc < 16) {
        if ((list >> inc) & 0b1) {
            count++;
        }
        inc++;
    }
    return (count);
}

void core_arm_block_dt(uint32_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rn = bitfield_readx(op, 16, 20);
    bool load = bitfield_read1(op, 20);
    bool writeback = bitfield_read1(op, 21);
    bool psr = bitfield_read1(op, 22);
    bool updown = bitfield_read1(op, 23);
    bool indexing = bitfield_read1(op, 24);
    uint32_t addr = *(regs->raw[rn]);
    uint32_t wbaddr;
    size_t i = 0;
    bool flush_pipeline = false;

    if (rn == R15) {
        exception_raise(EXCEPTION_UND_INSTR, 0x0);
    }

    if (indexing && updown) { // pre-increment
        wbaddr = addr + (count_register(bitfield_readx(op, 0, 16)) * 4);
        addr += 4;
    } else if (!indexing && updown) { // post-increment
        wbaddr = addr + (count_register(bitfield_readx(op, 0, 16)) * 4);
    } else if (indexing && !updown) { // pre-decrement
        addr -= (count_register(bitfield_readx(op, 0, 16)) * 4);
        wbaddr = addr;
    } else if (!indexing && !updown) { // post-decrement
        addr -= (count_register(bitfield_readx(op, 0, 16)) * 4);
        wbaddr = addr;
        addr += 4;
    }

    if (!psr) {
        while (i < 16) {
            if (bitfield_read1(op, i)) {
                if (load) {
                    *(regs->raw[i]) = mmu_read32(addr);
                } else {
                    if (i == 15) {
                        mmu_write32(addr, *(regs->raw[i]) + (12 - 4));
                    } else {
                        mmu_write32(addr, *(regs->raw[i]));
                    }
                }
                addr += 4;
            }
            i++;
        }
        if (writeback) {
            *(regs->raw[rn]) = wbaddr;
        }
        if (bitfield_read1(op, 15) && load) {
            core_flush_pipeline();
        }
    } else {
        if (load && bitfield_read1(op, 15)) {
            while (i < 16) {
                if (bitfield_read1(op, i)) {
                    *(regs->raw[i]) = mmu_read32(addr);
                    addr += 4;
                }
                i++;
            }
            if (writeback) {
                *(regs->raw[rn]) = wbaddr;
            }
            if (regs->spsr) {
                regs->spsr->raw = regs->cpsr->raw;
            }
            core_flush_pipeline();
        } else if (!load && bitfield_read1(op, 15)) {
            regs = core_get_opmode_regs(OPERATION_MODE_USER);
            while (i < 16) {
                if (bitfield_read1(op, i)) {
                    if (i == 15) {
                        mmu_write32(addr, *(regs->raw[i]) + (12 - 4));
                    } else {
                        mmu_write32(addr, *(regs->raw[i]));
                    }
                    addr += 4;
                }
                i++;
            }
        } else if (!bitfield_read1(op, 15)) {
            regs = core_get_opmode_regs(OPERATION_MODE_USER);
            while (i < 16) {
                if (bitfield_read1(op, i)) {
                    if (load) {
                        *(regs->raw[i]) = mmu_read32(addr);
                    } else {
                        mmu_write32(addr, *(regs->raw[i]));
                    }
                    addr += 4;
                }
                i++;
            }
        }
    }
}