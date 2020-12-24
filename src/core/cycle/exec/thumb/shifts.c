/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "core/cycle/exec.h"

void core_thumb_shifts(uint16_t op)
{
    struct thumb_regs *regs = core_get_thumb_regs();
    uint32_t rd = bitfield_readx(op, 0, 3);
    uint32_t rs = bitfield_readx(op, 3, 6);
    uint32_t off = bitfield_readx(op, 6, 11);
    uint32_t val = *(regs->raw[rs]);
    bool carry = false;


    switch (bitfield_readx(op, 11, 13))
    {
        case 0b00: // lsl
            if (off > 0) {
                carry = (val >> (32 - off)) & 0b1;
                val <<= off;
            } else {
                carry = regs->cpsr->carry;
            }
            break;
        case 0b01: // lsr
            if (off == 0) {
                off = 32;
            }
            regs->cpsr->carry = (val >> (off - 1)) & 0b1;
            val >>= off;
            break;
        case 0b10: // asr
            if (off == 0) {
                off = 32;
            }
            regs->cpsr->carry = (val >> (off - 1)) & 0b1;
            val = (int32_t)val >> off;
            break;
        default:
            goto err;
    }

    regs->cpsr->carry    = carry;
    regs->cpsr->zero     = !val;
    regs->cpsr->negative = (val >> 31) & 0b1;

    *(regs->raw[rd]) = val;

    err:
    panic("Invalid opcode %#04x", op);
}
