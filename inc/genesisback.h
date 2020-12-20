/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _GENESISBACK_H_
# define _GENESISBACK_H_

# include "def/def.h"
# include "def/access.h"
# include "def/status.h"
# include "def/generator.h"
# include "def/assert.h"
# include "io/log.h"

# define DEBUG_STATE_MASTER false

# define VERBOSE_RUN

void __noreturn panic(char const *fmt, ...);

#endif /* !_GENESISBACK_H_ */
