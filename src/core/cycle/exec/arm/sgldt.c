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

void core_arm_single_dt(uint32_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t off = bitfield_readx(op, 0, 12);
    uint32_t rd = (op >> 12) & 0xF;
    uint32_t rn = (op >> 16) & 0xF;
    uint32_t base = *(regs->raw[rn]);
    bool load = bitfield_read1(op, 20);
    bool writeback = bitfield_read1(op, 21);
    bool quantity = bitfield_read1(op, 22);
    bool updown = bitfield_read1(op, 23);
    bool indexing = bitfield_read1(op, 24);
    uint32_t addr;
    uint32_t wbaddr;

    if (bitfield_read1(op, 25) == 0b0) {
        // all comes good
    } else {
        off = core_exec_interpret_shift(*(regs->raw[off & 0xF]), (off >> 4) & 0xFF, false);
    }
    if (!updown) {
        wbaddr = base - off;
    } else {
        wbaddr = base + off;
    }

    if (!indexing) {
        addr = base;
    } else {
        addr = wbaddr;
    }

    if (!quantity && !load) { // store word
        mmu_write32(addr, *(regs->raw[rd]));
    } else if (quantity && !load) { // store byte
        mmu_write8(addr, *(regs->raw[rd]));
    } else if (!quantity && load) { // load word
        *(regs->raw[rd]) = mmu_read32(addr);
    } else if (quantity && load) { // load byte
        *(regs->raw[rd]) = mmu_read8(addr);
    } 

    if (indexing == false || writeback == true) {
        *(regs->raw[rn]) = wbaddr;
    }
}