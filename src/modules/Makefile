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
						init.o					\
						exit.o					\
						start.o					\
						stop.o					\
						info.o					\
						reset.o					\
						initialized.o			\
						running.o				\
						request.o				\
					)

sinclude $(local)/hooks/Makefile