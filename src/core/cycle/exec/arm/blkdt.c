/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "core/cycle/exec.h"
# include "mmu/mmu.h"

void core_arm_block_dt(uint32_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rn = bitfield_readx(op, 16, 20);
    uint32_t base = *(regs->raw[rn]);
    bool load = bitfield_read1(op, 20);
    bool writeback = bitfield_read1(op, 21);
    bool psr = bitfield_read1(op, 22);
    bool updown = bitfield_read1(op, 23);
    bool indexing = bitfield_read1(op, 24);
    uint32_t addr;
    uint32_t wbaddr;
    size_t i = 0;
    size_t off = 0;

    if (updown == false) {
        wbaddr = base - off;
    } else {
        wbaddr = base + off;
    }

    if (indexing == false) {
        addr = base;
    } else {
        addr = wbaddr;
    }

    if (!psr) {
        while (i < 16) {
            if (bitfield_read1(op, i)) {
                if (load) {
                    *(regs->raw[i]) = mmu_read32(addr);
                } else {
                    mmu_write32(addr, *(regs->raw[i]));
                }
                addr += 4;
                wbaddr += 4;
            }
            i++;
        }
        if (writeback) {
            *(regs->raw[rn]) = wbaddr;
        }
        if (load) {
            core_flush_pipeline();
        }
    } else {
        if (load && bitfield_read1(op, 15)) {
            while (i < 16) {
                if (bitfield_read1(op, i)) {
                    *(regs->raw[i]) = mmu_read32(addr);
                    addr += 4;
                    wbaddr += 4;
                }
                i++;
            }
            if (writeback) {
                *(regs->raw[rn]) = wbaddr;
            }
            if (regs->spsr) {
                regs->spsr->raw = regs->cpsr->raw;
            }
        } else if (!load && bitfield_read1(op, 15)) {
            regs = core_get_opmode_regs(OPERATION_MODE_USER);
            while (i < 16) {
                if (bitfield_read1(op, i)) {
                    *(regs->raw[i]) = mmu_read32(addr);
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