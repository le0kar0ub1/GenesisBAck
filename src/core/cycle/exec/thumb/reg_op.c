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

void core_thumb_reg_op(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    bool h2 = bitfield_read1(op, 6);
    bool h1 = bitfield_read1(op, 7);
    uint32_t rd = bitfield_readx(op, 0, 3) + (h1 * 8);
    uint32_t rs = bitfield_readx(op, 3, 6) + (h2 * 8);
    uint32_t op1, op2;

    if (h1 == 0 && h2 == 0)
        exception_raise(EXCEPTION_UND_INSTR);

    switch (bitfield_readx(op, 8, 10))
    {
        case 0b00:
            *(regs->raw[rd]) += *(regs->raw[rs]);
            if (rd == R15)
                core_flush_pipeline();
            break;
        case 0b01:
            op1 = *(regs->raw[rd]);
            op2 = *(regs->raw[rs]);
            regs->cpsr->zero = !(op1 - op2);
            regs->cpsr->negative = ((op1 - op2) >> 31) & 0b1;
            regs->cpsr->carry = usub32_carry(op1, op2);
            regs->cpsr->overflow = isub32_overflow(op1, op2);
            break;
        case 0b10:
            *(regs->raw[rd]) = *(regs->raw[rs]);
            if (rd == R15)
                core_flush_pipeline();
            break;
        default:
            exception_raise(EXCEPTION_UND_INSTR);
            break;
    }
}