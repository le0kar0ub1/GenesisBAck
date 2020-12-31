###############################################################################
##
##  This file is part of the GenesisBack project, and is made available under
##  the terms of the GNU General Public License version 3.
##
##  Copyright (C) 2020 - Leo Karoubi
##
###############################################################################

local = $(CALLED_LOCAL_DIRECTORY)

TARGET_OBJECTS	+= $(addprefix $(local),	\
						panic.o				\
						exceptions.o		\
						core.o				\
						arm7tdmi.o			\
					)

sinclude 	$(local)/cycle/Makefile