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

void core_arm_reg_hwdt(uint32_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rd = (op >> 12) & 0xF;
    uint32_t rn = (op >> 16) & 0xF;
    uint32_t off = bitfield_readx(op, 0, 4) | (bitfield_readx(op, 8, 12) << 4); 
    uint32_t base = *(regs->raw[rn]);
    bool load = bitfield_read1(op, 20);
    bool writeback = bitfield_read1(op, 21);
    bool updown = bitfield_read1(op, 23);
    bool indexing = bitfield_read1(op, 24);
    uint32_t addr;
    uint32_t wbaddr;
    uint32_t buf;

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

    switch ((bitfield_read1(op, 6) << 1) | bitfield_read1(op, 6))
    {
       case 0b00: // swap, the load/store bit is probably a non-sense in this context but it's not specified
            panic("swp hf unimplemented");
            break;
        case 0b01: // unsigned hw
            if (load) {
                *(regs->raw[rd]) = mmu_read16(addr);
            } else {
                mmu_write16(addr, *(regs->raw[rd]));
            }
            break;
        case 0b10: // signed byte
            if (load) {
                *(regs->raw[rd]) = (int32_t)(int8_t)mmu_read8(addr);
            } else {
                mmu_write8(addr, (int32_t)(int8_t)*(regs->raw[rd]));
            }
            break;
        case 0b11: // signed hw
            if (load) {
                *(regs->raw[rd]) = (int32_t)(int16_t)mmu_read16(addr);
            } else {
                mmu_write16(addr, (int32_t)(int16_t)*(regs->raw[rd]));
            }
            break;
    }

    if (indexing == false || writeback == true) {
        *(regs->raw[rn]) = wbaddr;
    }
}

void core_arm_imm_hwdt(uint32_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rm = bitfield_readx(op, 0, 4);
    uint32_t rd = (op >> 12) & 0xF;
    uint32_t rn = (op >> 16) & 0xF;
    uint32_t off = *(regs->raw[rm]); 
    uint32_t base = *(regs->raw[rn]);
    bool load = bitfield_read1(op, 20);
    bool writeback = bitfield_read1(op, 21);
    bool updown = bitfield_read1(op, 23);
    bool indexing = bitfield_read1(op, 24);
    uint32_t addr;
    uint32_t wbaddr;
    uint32_t buf;

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

    switch ((bitfield_read1(op, 6) << 1) | bitfield_read1(op, 6))
    {
       case 0b00: // swap, the load/store bit is probably a non-sense in this context but it's not specified
            panic("swp hf unimplemented");
            break;
        case 0b01: // unsigned hw
            if (load) {
                *(regs->raw[rd]) = mmu_read16(addr);
            } else {
                mmu_write16(addr, *(regs->raw[rd]));
            }
            break;
        case 0b10: // signed byte
            if (load) {
                *(regs->raw[rd]) = (int32_t)(int8_t)mmu_read8(addr);
            } else {
                mmu_write8(addr, (int32_t)(int8_t)*(regs->raw[rd]));
            }
            break;
        case 0b11: // signed hw
            if (load) {
                *(regs->raw[rd]) = (int32_t)(int16_t)mmu_read16(addr);
            } else {
                mmu_write16(addr, (int32_t)(int16_t)*(regs->raw[rd]));
            }
            break;
    }

    if (indexing == false || writeback == true) {
        *(regs->raw[rn]) = wbaddr;
    }
}
