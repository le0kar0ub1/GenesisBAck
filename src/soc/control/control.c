/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "soc/control.h"

struct control_iomem *io = NULL;

void control_init(void)
{
    io = (struct control_iomem *)CONTROL_IOMEM_BASE;
}

void control_exit(void)
{
    io = NULL;
}

void control_start(void)
{
}