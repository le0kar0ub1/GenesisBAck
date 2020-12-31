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

void core_thumb_sdt_reg(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rd = bitfield_readx(op, 0, 3);
    uint32_t rb = bitfield_readx(op, 3, 6);
    uint32_t ro = bitfield_readx(op, 6, 9);
    bool bw = bitfield_read1(op, 10);
    bool ls = bitfield_read1(op, 11);
    uint32_t addr = *(regs->raw[rb]) + *(regs->raw[ro]);

    if (bw && ls) { // load byte
        *(regs->raw[rd]) = mmu_read8(addr);
    } else if (!bw && ls) { // load word
        *(regs->raw[rd]) = mmu_read32(addr);
    } else if (bw && !ls) { // store byte
        mmu_write8(addr, *(regs->raw[rd]));
    } else if (!bw && !ls) { // store word
        mmu_write32(addr, *(regs->raw[rd]));
    }
}

void core_thumb_sdt_shw(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rd = bitfield_readx(op, 0, 3);
    uint32_t rb = bitfield_readx(op, 3, 6);
    uint32_t ro = bitfield_readx(op, 6, 9);
    bool sign = bitfield_read1(op, 10);
    bool half = bitfield_read1(op, 11);
    uint32_t addr = *(regs->raw[rb]) + *(regs->raw[ro]);

    if (sign && half) { // load signed halfword
        *(regs->raw[rd]) = (int32_t)(int16_t)mmu_read16(addr);
    } else if (!sign && half) { // load halfword 
        *(regs->raw[rd]) = mmu_read16(addr);
    } else if (sign && !half) { // load signed byte
        *(regs->raw[rd]) = (int32_t)(int8_t)mmu_read8(addr);
    } else if (!sign && !half) { // store halfword
        mmu_write16(addr, *(regs->raw[rd]));
    }
}

void core_thumb_sdt_imm(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rd = bitfield_readx(op, 0, 3);
    uint32_t rb = bitfield_readx(op, 3, 6);
    uint32_t off = bitfield_readx(op, 6, 11);
    bool bw = bitfield_read1(op, 10);
    bool ls = bitfield_read1(op, 11);
    uint32_t addr = *(regs->raw[rb]);
    
    if (bw) {
        addr += off;
    } else {
        addr += off << 2;
    }

    if (bw && ls) { // load byte
        *(regs->raw[rd]) = mmu_read8(addr);
    } else if (!bw && ls) { // load word
        *(regs->raw[rd]) = mmu_read32(addr);
    } else if (bw && !ls) { // store byte
        mmu_write8(addr, *(regs->raw[rd]));
    } else if (!bw && !ls) { // store word
        mmu_write32(addr, *(regs->raw[rd]));
    }
}

void core_thumb_sdt_hw(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rd = bitfield_readx(op, 0, 3);
    uint32_t rb = bitfield_readx(op, 3, 6);
    uint32_t off = bitfield_readx(op, 6, 11);
    bool ls = bitfield_read1(op, 11);
    uint32_t addr = *(regs->raw[rb]) + off;

    if (ls) { // load word
        *(regs->raw[rd]) = mmu_read16(addr);
    } else if (!ls) { // store word
        mmu_write16(addr, *(regs->raw[rd]));
    }
}

void core_thumb_sdt_sp_rel(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t off = bitfield_readx(op, 0, 8) << 2;
    uint32_t rd = bitfield_readx(op, 8, 11);
    bool ls = bitfield_read1(op, 11);

    if (ls) { // load
        *(regs->raw[rd]) = mmu_read32(*(regs->r13) + off);
    } else if (!ls) { // store
        mmu_write32(*(regs->r13) + off, *(regs->raw[rd]));
    }
}

void core_thumb_ldr_pc(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t imm = bitfield_readx(op, 0, 8) << 2;
    uint32_t rd = bitfield_readx(op, 8, 11);

    *(regs->raw[rd]) = mmu_read32(ALIGN4(*(regs->r15)) + imm);
}

void core_thumb_push_pop_reg(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    bool link = bitfield_read1(op, 8);
    ssize_t i;
    
    if (!bitfield_read1(op, 11)) { // push
        if (link) {
            *(regs->r13) -= 4;
            mmu_write32(*(regs->r13), *(regs->r14));
        }
        i = 7;
        while (i >= 0) {
            if (bitfield_read1(op, i)) {
                *(regs->r13) -= 4;
                mmu_write32(*(regs->r13), *(regs->raw[i]));
            }
            i--;
        }
    } else { // pop
        i = 0;
        while (i <= 7) {
            if (bitfield_read1(op, i)) {
                *(regs->raw[i]) = mmu_read32(*(regs->r13));
                *(regs->r13) += 4;
            }
            i++;
        }
        if (link) {
            *(regs->r15) = mmu_read32(*(regs->r13));
            *(regs->r13) += 4;
            core_flush_pipeline();
        }
    }
}

void core_thumb_mult_load_store(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rd = bitfield_readx(op, 8, 11);
    bool ls = bitfield_read1(op, 11);
    ssize_t i;

    if (!ls) { // store
        i = 0;
        while (i <= 7) {
            if (bitfield_read1(op, i)) {
                mmu_write32(*(regs->raw[rd]), *(regs->raw[i]));
                *(regs->raw[rd]) += 4;
            }
            i++;
        }
    } else { // load
        i = 0;
        while (i <= 7) {
            if (bitfield_read1(op, i)) {
                *(regs->raw[i]) = mmu_read32(*(regs->raw[rd]));
                *(regs->raw[rd]) += 4;
            }
            i++;
        }
    }
}
