/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _EMULATOR_MMU_MMU_H_
# define _EMULATOR_MMU_MMU_H_

# include "genesisback.h"

/**
 * TODO: Macro or inline fonction ?
 */
hostaddr_t trns_to_host(virtaddr_t virt);
virtaddr_t trns_to_virt(hostaddr_t host);

#endif /* _EMULATOR_MMU_MMU_H_ */