/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _CORE_CYCLE_ROUTE_H_
# define _CORE_CYCLE_ROUTE_H_

# include "core/core.h"
# include "mmu/mmu.h"

/**
 * Return the exec cycle handler
 */
void *cycle_route_thumb(uint32_t op);
void *cycle_route_arm(uint32_t op);

#endif /* _CORE_CYCLE_ROUTE_H_ */