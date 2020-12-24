/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "core/cycle/exec.h"

void core_thumb_add_sub(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rd  = bitfield_readx(op, 0, 3);
    uint32_t rs  = bitfield_readx(op, 3, 6);
    uint32_t op2;

    if (bitfield_read1(op, 10) == 0b0) {
        op2 = *(regs->raw[bitfield_readx(op, 6, 9)]);
    } else {
        op2 = bitfield_readx(op, 6, 9);
    }

    if (bitfield_read1(op, 9) == 0b0) {
        *(regs->raw[rd]) = *(regs->raw[rs]) + op2;
        regs->cpsr->carry = uadd32_carry(*(regs->raw[rs]), op2);
        regs->cpsr->overflow = iadd32_overflow(*(regs->raw[rs]), op2);
    } else {
        *(regs->raw[rd]) = *(regs->raw[rs]) - op2;
        regs->cpsr->carry = usub32_carry(*(regs->raw[rs]), op2);
        regs->cpsr->overflow = isub32_overflow(*(regs->raw[rs]), op2);
    }
    
    regs->cpsr->zero = !(*(regs->raw[rd]));
    regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
}