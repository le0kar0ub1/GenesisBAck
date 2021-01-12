/******************************************************************************
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _DEF_GENERATOR_H_
# define _DEF_GENERATOR_H_

# include <def/def.h>

# define _CONCAT(a, b)  a##b
# define CONCAT(a, b)   _CONCAT(a, b)

# define _STRINGIFY(a)  #a
# define STRINGIFY(a)   _STRINGIFY(a)

#endif /* !_DEF_GENERATOR_H_ */
