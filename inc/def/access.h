/********************************************************************************
** 
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _DEF_ACCESS_H_
# define _DEF_ACCESS_H_

/**
 * Access privilege flags, usable everywhere
*/
enum access_flag
{
    Nop = 0b0000,
    A   = 0b1000,
    R   = 0b0100,
    W   = 0b0010,
    X   = 0b0001,
    RW  = 0b0110,
    RX  = 0b0101,
    RWX = 0b0111,
};

typedef enum access_flag access_flag_t;

# define IS_READABLE(x)   (x & R)
# define IS_WRITABLE(x)   (x & W)
# define IS_EXECUTABLE(x) (x & X)

#endif /* !_DEF_ACCESS_H_ */
