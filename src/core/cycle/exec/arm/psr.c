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

void core_arm_mrs(uint32_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rd = (op >> 12) & 0xF;

    if (bitfield_read1(op, 22) == 0b0 && rd != R15) {
        *(regs->raw[rd]) = regs->cpsr->raw;
    } else if (regs->cpsr->opmode != OPERATION_MODE_USER && rd != R15) {
        *(regs->raw[rd]) = regs->spsr->raw;
    } else {
        exception_raise(EXCEPTION_UND_INSTR);
    }
}

void core_arm_msr(uint32_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t rs = op & 0xF;

    printf("%u\n", *(regs->raw[rs]));
    if (bitfield_read1(op, 22) == 0b0 && regs->cpsr->opmode != OPERATION_MODE_USER && rs != R15) {
        regs->cpsr->raw = *(regs->raw[rs]);
    } else if (regs->cpsr->opmode != OPERATION_MODE_USER && rs != R15) {
        regs->spsr->raw = *(regs->raw[rs]);
    } else {
        exception_raise(EXCEPTION_UND_INSTR);
    }
}

void core_arm_msrf(uint32_t op)
{
    struct opmode_regs *regs = core_get_context_regs();
    uint32_t op2;

    if (bitfield_read1(op, 25) == 0b0) { // register
        if ((op & 0xF) == R15)
        exception_raise(EXCEPTION_UND_INSTR);
        op2 = *(regs->raw[(op & 0xF)]);
    } else { // immediate
        op2 = core_exec_imm8_rotate4(op & 0xFF, (op >> 8) & 0xF);
    }

    if (bitfield_read1(op, 22) == 0b0 && regs->cpsr->opmode != OPERATION_MODE_USER) {
        regs->cpsr->raw = op2;
    } else if (regs->cpsr->opmode != OPERATION_MODE_USER) {
        regs->spsr->raw = op2;
    } else {
        exception_raise(EXCEPTION_UND_INSTR);
    }
}