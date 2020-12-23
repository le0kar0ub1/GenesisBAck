/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _CORE_CYCLE_EXEC_H_
# define _CORE_CYCLE_EXEC_H_

# include "core/core.h"
# include "mmu/mmu.h"

void core_arm_data_processing(uint32_t op);
void core_arm_multiply(uint32_t op);
void core_arm_branch_exchange(uint32_t op);
void core_arm_reg_data_transfer(uint32_t op);
void core_arm_imm_data_transfer(uint32_t op);
void core_arm_undefined(uint32_t op);
void core_arm_single_data_transfer(uint32_t op);
void core_arm_block_data_trabsfer(uint32_t op);
void core_arm_branch(uint32_t op);
void core_arm_coprocessor_data_transfer(uint32_t op);
void core_arm_coprocessor_data_operation(uint32_t op);
void core_arm_coprocessor_register_transfer(uint32_t op);
void core_arm_swi(uint32_t op);

void core_thumb_add_sub(uint16_t op);
void core_thumb_mv_shifted_reg(uint16_t op);
void core_thumb_imm_op(uint16_t op);
void core_thumb_alu_op(uint16_t op);
void core_thumb_hireg_op_br_exch(uint16_t op);
void core_thumb_pc_rel_load(uint16_t op);
void core_thumb_reg_off_load_store(uint16_t op);
void core_thumb_sign_ext_load_store(uint16_t op);
void core_thumb_immoff_load_store(uint16_t op);
void core_thumb_hf_load_store(uint16_t op);
void core_thumb_sp_rel_load_store(uint16_t op);
void core_thumb_load_addr(uint16_t op);
void core_thumb_add_off_sp(uint16_t op);
void core_thumb_push_pop_reg(uint16_t op);
void core_thumb_swi(uint16_t op);
void core_thumb_conditional_branch(uint16_t op);
void core_thumb_mult_load_store(uint16_t op);
void core_thumb_unconditional_branch(uint16_t op);
void core_thumb_branch_link(uint16_t op);

uint32_t core_exec_interpret_shifts(uint32_t val, uint32_t shift, bool carry_mod);

#endif /* _CORE_CYCLE_EXEC_H_ */