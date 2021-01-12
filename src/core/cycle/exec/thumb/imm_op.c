/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <core/cycle/exec.h>

void core_thumb_imm_op(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t off = bitfield_readx(op, 0, 8);
    uint32_t rd  = bitfield_readx(op, 8, 11);

    switch (bitfield_readx(op, 11, 13))
    {
        case 0b00: // mov
            *(regs->raw[rd]) = off;
            regs->cpsr->zero = !(*(regs->raw[rd]));
            regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            break;
        case 0b01: // cmp
            regs->cpsr->carry = usub32_carry(*(regs->raw[rd]), off);
            regs->cpsr->overflow = isub32_overflow(*(regs->raw[rd]), off);
            regs->cpsr->zero = !(*(regs->raw[rd]) - off);
            regs->cpsr->negative = ((*(regs->raw[rd]) - off) >> 31) & 0b1;
            break;
        case 0b10: // add
            *(regs->raw[rd]) += off;
            regs->cpsr->carry = uadd32_carry(*(regs->raw[rd]), off);
            regs->cpsr->overflow = iadd32_overflow(*(regs->raw[rd]), off);
            regs->cpsr->zero = !(*(regs->raw[rd]));
            regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            break;
        case 0b11: // sub
            *(regs->raw[rd]) -= off;
            regs->cpsr->carry = usub32_carry(*(regs->raw[rd]), off);
            regs->cpsr->overflow = isub32_overflow(*(regs->raw[rd]), off);
            regs->cpsr->zero = !(*(regs->raw[rd]));
            regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            break;
        default:
            break;
    }
}