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
						branch.o				\
						alu.o					\
						psr.o					\
						multiply.o				\
						sgldt.o					\
						hwsdt.o					\
						dataswap.o				\
						undefined.o				\
						swi.o					\
						blkdt.o					\
					)

sinclude $(local)/coproc/Makefile