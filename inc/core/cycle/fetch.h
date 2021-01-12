/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _CORE_CYCLE_FECTH_H_
# define _CORE_CYCLE_FECTH_H_

# include <core/core.h>
# include <mmu/mmu.h>

/**
 * The public set of function, used to fetch an instruction
 * As an emulator, the mode checkup has not to be everywhere, the caller must know the machine state
 */
uint32_t core_fetch_arm(void);
uint16_t core_fetch_thumb(void);

#endif /* _CORE_CYCLE_FECTH_H_ */