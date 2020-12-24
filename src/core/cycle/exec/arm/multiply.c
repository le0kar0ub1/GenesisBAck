/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "core/cycle/exec.h"
# include "core/exceptions.h"

void core_arm_multiply(uint32_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rm = (op >> 0) & 0xF;
    uint32_t rs = (op >> 8) & 0xF;
    uint32_t rn = (op >> 12) & 0xF;
    uint32_t rd = (op >> 16) & 0xF;

    if (bitfield_read1(op, 21) == 0b0) {
        *(regs->raw[rd]) = (*(regs->raw[rm])) * (*(regs->raw[rs]));
    } else {
        *(regs->raw[rd]) = (*(regs->raw[rm])) * (*(regs->raw[rs])) + (*(regs->raw[rn]));
    }

    if (bitfield_read1(op, 20) == 0b1) {
        regs->cpsr->zero = !(*(regs->raw[rd]));
        regs->cpsr->negative = (*(regs->raw[rd])) >> 31;
        // Carry flag take a "meaningless value" lol
    }
}

void core_arm_multiply_long(uint32_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rm = (op >> 0) & 0xF;
    uint32_t rs = (op >> 8) & 0xF;
    uint32_t rdlo = (op >> 12) & 0xF;
    uint32_t rdhi = (op >> 16) & 0xF;
    bool sign = bitfield_read1(op, 22);

    if (rdlo == rdhi)
        exception_raise(EXCEPTION_UND_INSTR);
    if (bitfield_read1(op, 21) == 0b0) {
        if (sign == 0) {
            uint64_t res = (uint64_t)(*(regs->raw[rm])) * (uint64_t)(*(regs->raw[rs]));
            *(regs->raw[rdlo]) = res & ((1ul << 32ul) - 1ul);
            *(regs->raw[rdhi]) = res >> 32;
        } else {
            int64_t res = (int64_t)(*(regs->raw[rm])) * (int64_t)(*(regs->raw[rs]));
            *(regs->raw[rdlo]) = res & ((1ul << 32ul) - 1ul);
            *(regs->raw[rdhi]) = res >> 32;
        }
    } else {
        if (sign == 0) {
            uint64_t add = (uint64_t)*(regs->raw[rdlo]) | ((uint64_t)*(regs->raw[rdhi]) << 32);
            uint64_t res = (uint64_t)(*(regs->raw[rm])) * (uint64_t)(*(regs->raw[rs])) + (uint64_t)add;
            *(regs->raw[rdlo]) = res & ((1ul << 32ul) - 1ul);
            *(regs->raw[rdhi]) = res >> 32;
        } else {
            uint64_t add = (uint64_t)*(regs->raw[rdlo]) | ((uint64_t)*(regs->raw[rdhi]) << 32);
            int64_t res = (int64_t)(*(regs->raw[rm])) * (int64_t)(*(regs->raw[rs])) + (int64_t)add;
            *(regs->raw[rdlo]) = res & ((1ul << 32ul) - 1ul);
            *(regs->raw[rdhi]) = res >> 32;
        }
    }

    if (bitfield_read1(op, 20) == 0b1) {
        regs->cpsr->zero = !(*(regs->raw[rdlo])) && !(*(regs->raw[rdhi]));
        regs->cpsr->negative = (*(regs->raw[rdhi])) >> 31;
        // Carry & overflow flag take a "meaningless value" : lol
    }
}