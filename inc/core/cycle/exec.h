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

#endif /* _CORE_CYCLE_EXEC_H_ */