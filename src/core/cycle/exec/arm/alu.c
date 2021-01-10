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
 * The ALU job
 * https://pdf.dzsc.com/ARM/ARM7TDMI.pdf  page 52
 */
void core_arm_alu(uint32_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rd = (op >> 12) & 0xF;
    uint32_t rn = (op >> 16) & 0xF;
    uint32_t op1 = *(regs->raw[rn]);
    uint32_t op2;
    bool condition = bitfield_read1(op, 20);

    if (rn != R15 && bitfield_read1(op, 25) == 0b0) {
        op2 = core_exec_interpret_shift(*(regs->raw[op & 0xF]), (op >> 4) & 0xFF, condition && rd != R15);
    } else if (rn != R15 && bitfield_read1(op, 25) == 0b1) {
        uint32_t imm = op & 0xFF;
        uint32_t rot = ((op >> 8) & 0xF);
        op2 = core_exec_imm8_rotate4(imm, rot);
    }

    switch (bitfield_readx(op, 21, 25))
    {
        case 0b0000: // AND (op1 AND op2)
            *(regs->raw[rd]) = op1 & op2;
            if ((condition && rd != R15) || (!condition && rd == R15)) {
                regs->cpsr->zero = !(*(regs->raw[rd]));
                regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            }
            break;
        case 0b0001: // EOR (op1 XOR op2)
            *(regs->raw[rd]) = op1 ^ op2;
            if ((condition && rd != R15) || (!condition && rd == R15)) {
                regs->cpsr->zero = !(*(regs->raw[rd]));
                regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            }
            break;
        case 0b0010: // SUB (op1 - op2)
            *(regs->raw[rd]) = op1 - op2;
            if ((condition && rd != R15) || (!condition && rd == R15)) {
                regs->cpsr->zero = !(*(regs->raw[rd]));
                regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
                regs->cpsr->carry = usub32_carry(op1, op2);
                regs->cpsr->overflow = isub32_overflow(op1, op2);
            }
            break;
        case 0b0011: // RSB (op2 - op1)
            *(regs->raw[rd]) = op2 - op1;
            if ((condition && rd != R15) || (!condition && rd == R15)) {
                regs->cpsr->zero = !(*(regs->raw[rd]));
                regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
                regs->cpsr->carry = usub32_carry(op2, op1);
                regs->cpsr->overflow = isub32_overflow(op2, op1);
            }
            break;
        case 0b0100: // ADD (op1 + op2)
            *(regs->raw[rd]) = op1 + op2;
            if ((condition && rd != R15) || (!condition && rd == R15)) {
                regs->cpsr->zero = !(*(regs->raw[rd]));
                regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
                regs->cpsr->carry = uadd32_carry(op1, op2);
                regs->cpsr->overflow = iadd32_overflow(op1, op2);
            }
            break;
        case 0b0101: // ADC (op1 + op2 + carry)
            *(regs->raw[rd]) = op1 + op2 + regs->cpsr->carry;
            if ((condition && rd != R15) || (!condition && rd == R15)) {
                regs->cpsr->zero = !(*(regs->raw[rd]));
                regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
                regs->cpsr->carry = uadd32_carry(op1, op2);
                regs->cpsr->carry |= uadd32_carry(op1 + op2, regs->cpsr->carry);
                regs->cpsr->overflow = iadd32_overflow(op1, op2);
                regs->cpsr->overflow |= iadd32_overflow(op1 + op2, regs->cpsr->carry);
            }
            break;
        case 0b0110: // SBC (op1 - op2 + carry - 1)
            *(regs->raw[rd]) = op1 - op2 + regs->cpsr->carry - 1;
            if ((condition && rd != R15) || (!condition && rd == R15)) {
                regs->cpsr->zero = !(*(regs->raw[rd]));
                regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
                regs->cpsr->carry = usub32_carry(op1, op2);
                regs->cpsr->carry |= uadd32_carry(op1 - op2, regs->cpsr->carry);
                regs->cpsr->carry |= usub32_carry(op1 - op2 + regs->cpsr->carry, 1);
                regs->cpsr->overflow = isub32_overflow(op1, op2);
                regs->cpsr->overflow |= iadd32_overflow(op1 - op2, regs->cpsr->carry);
                regs->cpsr->overflow |= isub32_overflow(op1 - op2 + regs->cpsr->carry, 1);
            }
            break;
        case 0b0111: // RSC (op2 - op1 + carry - 1)
            *(regs->raw[rd]) = op2 - op1 + regs->cpsr->carry - 1;
            if ((condition && rd != R15) || (!condition && rd == R15)) {
                regs->cpsr->zero = !(*(regs->raw[rd]));
                regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
                regs->cpsr->carry = usub32_carry(op2, op1);
                regs->cpsr->carry |= uadd32_carry(op2 - op1, regs->cpsr->carry);
                regs->cpsr->carry |= usub32_carry(op2 - op1 + regs->cpsr->carry, 1);
                regs->cpsr->overflow = isub32_overflow(op2, op1);
                regs->cpsr->overflow |= iadd32_overflow(op2 - op1, regs->cpsr->carry);
                regs->cpsr->overflow |= isub32_overflow(op2 - op1 + regs->cpsr->carry, 1);
            }
            break;
        case 0b1000: // TST (as AND, but result is not written)
            if ((condition && rd != R15) || (!condition && rd == R15)) {
                regs->cpsr->zero = !(op1 & op2);
                regs->cpsr->negative = ((op1 & op2) >> 31) & 0b1;
            }
            break;
        case 0b1001: // TEQ (as EOR, but result is not written)
            if ((condition && rd != R15) || (!condition && rd == R15)) {
                regs->cpsr->zero = !(op1 ^ op2);
                regs->cpsr->negative = ((op1 ^ op2) >> 31) & 0b1;
            }
            break;
        case 0b1010: // CMP (as SUB, but result is not written)
            if ((condition && rd != R15) || (!condition && rd == R15)) {
                regs->cpsr->zero = !(op1 - op2);
                regs->cpsr->negative = ((op1 - op2) >> 31) & 0b1;
                regs->cpsr->carry = usub32_carry(op1, op2);
                regs->cpsr->overflow = isub32_overflow(op1, op2);
            }
            break;
        case 0b1011: // CMN (as ADD, but result is not written)
            if ((condition && rd != R15) || (!condition && rd == R15)) {
                regs->cpsr->zero = !(op1 + op2);
                regs->cpsr->negative = ((op1 + op2) >> 31) & 0b1;
                regs->cpsr->carry = uadd32_carry(op1, op2);
                regs->cpsr->overflow = iadd32_overflow(op1, op2);
            }
            break;
        case 0b1100: // ORR (op1 OR op2)
            *(regs->raw[rd]) = op1 | op2;
            if ((condition && rd != R15) || (!condition && rd == R15)) {
                regs->cpsr->zero = !(*(regs->raw[rd]));
                regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            }
            break;
        case 0b1101: // MOV (op2, op1 is ignored)
            *(regs->raw[rd]) = op2;
            if ((condition && rd != R15) || (!condition && rd == R15)) {
                regs->cpsr->zero = !(*(regs->raw[rd]));
                regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            }
            break;
        case 0b1110: // BIC (op1 AND NOT op2)
            *(regs->raw[rd]) = op1 & ~op2;
            if ((condition && rd != R15) || (!condition && rd == R15)) {
                regs->cpsr->zero = !(*(regs->raw[rd]));
                regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            }
            break;
        case 0b1111: // MVN (NOT op2, op1 is ignored)
            *(regs->raw[rd]) = ~op2;
            if ((condition && rd != R15) || (!condition && rd == R15)) {
                regs->cpsr->zero = !(*(regs->raw[rd]));
                regs->cpsr->negative = ((*(regs->raw[rd])) >> 31) & 0b1;
            }
            break;
        default:
            break;
    }
    if (condition && rd == R15 && regs->cpsr->opmode != OPERATION_MODE_USER) {
        *(regs->cpsr) = *(regs->spsr);
    }
}
