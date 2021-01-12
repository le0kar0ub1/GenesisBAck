/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _GBA_TIMER_H_
# define _GBA_TIMER_H_

# include <genesisback.h>

# define TIMER_IOMEM_BASE 0x4000100

struct timer_iomem
{
    uint16_t tm0_counter; /* Timer 0 Counter/Reload */
    uint16_t tm0_ctrl; /* Timer 0 Control */
    uint16_t tm1_counter; /* Timer 1 Counter/Reload */
    uint16_t tm1_ctrl; /* Timer 1 Control */
    uint16_t tm2_counter; /* Timer 2 Counter/Reload */
    uint16_t tm2_ctrl; /* Timer 2 Control */
    uint16_t tm3_counter; /* Timer 3 Counter/Reload */
    uint16_t tm3_ctrl; /* Timer 3 Control */
};

#endif /* _GBA_TIMER_H_ */