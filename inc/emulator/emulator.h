/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _EMULATOR_EMULATOR_H_
# define _EMULATOR_EMULATOR_H_

# include <def/def.h>

void signal_init(void);

void __noreturn _panic(char const *anywhere, char const *fmt, ...);
# define panic(...) _panic(__func__, __VA_ARGS__)

#endif /* _EMULATOR_EMULATOR_H_ */