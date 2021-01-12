/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <core/cycle/exec.h>

void core_thumb_alu(uint16_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rd  = bitfield_readx(op, 0, 3);
    uint32_t rs  = bitfield_readx(op, 3, 6);
    uint32_t op1 = *(regs->raw[rd]);
    uint32_t op2 = *(regs->raw[rs]);

    switch (bitfield_readx(op, 6, 10))
    {
        case 0b0000: // AND (op1 AND op2)
            *(regs->raw[rd]) = op1 & op2;
            regs->cpsr->zero = !(*(regs->raw[rd]));
            regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            break;
        case 0b0001: // EOR (op1 XOR op2)
            *(regs->raw[rd]) = op1 ^ op2;
            regs->cpsr->zero = !(*(regs->raw[rd]));
            regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            break;
        case 0b0010: // LSL
            if (op2 > 1 && op2 < 32) {
                regs->cpsr->carry = (op1 >> (32 - op2)) & 0b1;
                op1 <<= op2;
            } else if (op2 >= 32) {
                op1 = 0;
                regs->cpsr->carry = 0;
            }
            *(regs->raw[rd]) = op1;
            regs->cpsr->zero = !op1;
            regs->cpsr->negative = (op1 >> 31) & 0b1;
            break;
        case 0b0011: // LSR
            if (op2 > 1 && op2 < 32) {
                regs->cpsr->carry = (op1 >> (op2 - 1)) & 0b1;
                op1 >>= op2;
            } else if (op2 >= 32) {
                op1 = 0;
                regs->cpsr->carry = 0;
            }
            *(regs->raw[rd]) = op1;
            regs->cpsr->zero = !op1;
            regs->cpsr->negative = (op1 >> 31) & 0b1;
            break;
        case 0b0100: // ASR
            if (op2 > 1 && op2 < 32) {
                regs->cpsr->carry = (op1 >> (op2 - 1)) & 0b1;
                op1 = (int32_t)op1 >> op2;
            } else if (op2 >= 32) {
                op1 = 0;
                regs->cpsr->carry = 0;
            }
            *(regs->raw[rd]) = op1;
            regs->cpsr->zero = !op1;
            regs->cpsr->negative = (op1 >> 31) & 0b1;
            break;
        case 0b0101: // ADC (op1 + op2 + carry)
            *(regs->raw[rd]) = op1 + op2 + regs->cpsr->carry;
            regs->cpsr->zero = !(*(regs->raw[rd]));
            regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            regs->cpsr->carry = uadd32_carry(op1, op2);
            regs->cpsr->carry |= uadd32_carry(op1 + op2, regs->cpsr->carry);
            regs->cpsr->overflow = iadd32_overflow(op1, op2);
            regs->cpsr->overflow |= iadd32_overflow(op1 + op2, regs->cpsr->carry);
            break;
        case 0b0110: // SBC (op1 - op2 + carry - 1)
            *(regs->raw[rd]) = op1 - op2 + regs->cpsr->carry - 1;
            regs->cpsr->zero = !(*(regs->raw[rd]));
            regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            regs->cpsr->carry = usub32_carry(op1, op2);
            regs->cpsr->carry |= uadd32_carry(op1 - op2, regs->cpsr->carry);
            regs->cpsr->carry |= usub32_carry(op1 - op2 + regs->cpsr->carry, 1);
            regs->cpsr->overflow = isub32_overflow(op1, op2);
            regs->cpsr->overflow |= iadd32_overflow(op1 - op2, regs->cpsr->carry);
            regs->cpsr->overflow |= isub32_overflow(op1 - op2 + regs->cpsr->carry, 1);
            break;
        case 0b0111: // ROR
            op2 %= 32; // No fun while rotate for nothing
            if (op2 > 0 && op < 32) {
                regs->cpsr->carry = (op1 >> (op2 - 1)) & 0b1;
                op1 = (op1 >> op2) | (op1 << (32 - op2));
            } else if (op == 32) {
                regs->cpsr->carry = (op1 >> 31) & 0b1;
            }
            *(regs->raw[rd]) = op1;
            regs->cpsr->zero = !op1;
            regs->cpsr->negative = (op1 >> 31) & 0b1;
            break;
        case 0b1000: // TST (as AND, but result is not written)
            regs->cpsr->zero = !(op1 & op2);
            regs->cpsr->negative = ((op1 & op2) >> 31) & 0b1;
            break;
        case 0b1001: // NEG
            *(regs->raw[rd]) = -op2;
            regs->cpsr->zero = !(*(regs->raw[rd]));
            regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            regs->cpsr->carry = usub32_carry(0, op2);
            regs->cpsr->overflow = isub32_overflow(0, op2);
            break;
        case 0b1010: // CMP (as SUB, but result is not written)
            regs->cpsr->zero = !(op1 - op2);
            regs->cpsr->negative = ((op1 - op2) >> 31) & 0b1;
            regs->cpsr->carry = usub32_carry(op1, op2);
            regs->cpsr->overflow = isub32_overflow(op1, op2);
            break;
        case 0b1011: // CMN (as ADD, but result is not written)
            regs->cpsr->zero = !(op1 + op2);
            regs->cpsr->negative = ((op1 + op2) >> 31) & 0b1;
            regs->cpsr->carry = uadd32_carry(op1, op2);
            regs->cpsr->overflow = iadd32_overflow(op1, op2);
            break;
        case 0b1100: // ORR (op1 OR op2)
            *(regs->raw[rd]) = op1 | op2;
            regs->cpsr->zero = !(*(regs->raw[rd]));
            regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            break;
        case 0b1101: // MUL
            *(regs->raw[rd]) = op1 * op2;
            regs->cpsr->zero = !(*(regs->raw[rd]));
            regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            break;
        case 0b1110: // BIC (op1 AND NOT op2)
            *(regs->raw[rd]) = op1 & ~op2;
            regs->cpsr->zero = !(*(regs->raw[rd]));
            regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            break;
        case 0b1111: // MVN (NOT op2, op1 is ignored)
            *(regs->raw[rd]) = ~op2;
            regs->cpsr->zero = !(*(regs->raw[rd]));
            regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            break;
        default:
            break;
    }
}