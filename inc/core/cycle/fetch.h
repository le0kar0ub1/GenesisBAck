/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _MACHINE_GBA_CPU_CYCLE_FECTH_H_
# define _MACHINE_GBA_CPU_CYCLE_FECTH_H_

# include "machine/gba/cpu/core.h"

/**
 * The public set of function, used to fetch an instruction
 * As an emulator, the mode checkup has not to be everywhere, the caller must know the machine state
 */
uint32_t cpu_fetch_instr32(void);
uint32_t cpu_fetch_arm_state(void) __attribute__((alias("cpu_fetch_instr32")));
uint16_t cpu_fetch_instr16(void);
uint16_t cpu_fetch_thumb_state(void) __attribute__((alias("cpu_fetch_instr16")));

#endif /* _MACHINE_GBA_CPU_CYCLE_FECTH_H_ */