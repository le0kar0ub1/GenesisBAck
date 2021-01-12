/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <core/cycle/exec.h>
# include <core/exceptions.h>

void core_thumb_swi(uint16_t op)
{
    uint32_t hdl = bitfield_readx(op, 0, 8);

    exception_raise(EXCEPTION_SWI, hdl);
}
