###############################################################################
##
##  This file is part of the GenesisBack project, and is made available under
##  the terms of the GNU General Public License version 3.
##
##  Copyright (C) 2020 - Leo Karoubi
##
###############################################################################

local = $(CALLED_LOCAL_DIRECTORY)

TARGET_OBJECTS	+= $(addprefix $(local),		\
					)

sinclude $(local)/dma/Makefile			\
		 $(local)/system/Makefile		\
		 $(local)/keypad/Makefile		\
		 $(local)/sound/Makefile		\
		 $(local)/timer/Makefile		\
		 $(local)/video/Makefile		\
		 $(local)/serial/Makefile		\
		 $(local)/interrupt/Makefile	\
		 $(local)/cartridge/Makefile	\
