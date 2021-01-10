/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "core/core.h"
# include "core/cycle/exec.h"

/**
 * Interpret an encoded shift for execution constraint
 * https://pdf.dzsc.com/ARM/ARM7TDMI.pdf page 54
 */
uint32_t core_exec_interpret_shift(uint32_t val, uint32_t shift, bool carry_mod)
{
    uint32_t base;
    uint32_t stype = (shift >> 1) & 0x3;
    bool carry = 0;
    struct register_psr cpsr = register_read_cpsr();

    if (bitfield_read1(shift, 0) == 0) { // immediate value
        base = (shift >> 3) & 0x1F;
    } else { // register
        base = register_read32((shift >> 4) & 0xF) & 0xFF;
    }

    // when base is 0, there are particular handling
    switch (stype)
    {
        case 0b00: // logical left
            if (base == 0) {
                carry = cpsr.carry;
            } else {
                carry = (val >> (32 - base)) & 0b1;
                val = val << base;
            }
            break;
        case 0b01: // logical right
            if (base == 0) {
                base = 32;
            }
            carry = (val >> (base - 1)) & 0b1;
            val = val >> base;
            break;
        case 0b10: // arithmetic right
            if (base == 0) {
                base = 32;
            }
            carry = (val >> (base - 1)) & 0b1;
            val = ((int32_t)val) >> base;
            break;
        case 0b11: // rotate right
            if (base == 0) { // Rotate right extended
                carry = val & 0b1;
                val = (val >> 1) | (cpsr.carry << 31);
            } else {
                carry = (val >> (base - 1)) & 0b1;
                val = (val >> base) | (val << (32 - base));
            }
            break;
        default:
            break;
    }
    if (carry_mod)
        register_write_cpsr(cpsr.raw);
    return (val);
}

/**
 * Core apply a imm8 rotate4
 */
uint32_t core_exec_imm8_rotate4(uint32_t imm, uint32_t rotate)
{
    rotate *= 2;
    imm = (imm >> rotate) | (imm << (32 - rotate));
    return (imm);
}