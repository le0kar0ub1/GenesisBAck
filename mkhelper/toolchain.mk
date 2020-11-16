###############################################################################
##
##  This file is part of the GenesisBack project, and is made available under
##  the terms of the GNU General Public License version 3.
##
##  Copyright (C) 2020 - Leo Karoubi
##
###############################################################################

export TOOLCHAIN_GNUBASE := $(PROJECT_PATH)/mktoolchain/toolchain/bin/anyhow

export CC		:=	$(TOOLCHAIN_GNUBASE)gcc
export AS		:=	$(TOOLCHAIN_GNUBASE)as
export AR		:=	$(TOOLCHAIN_GNUBASE)ar
export LD		:=	$(TOOLCHAIN_GNUBASE)ld
export OBJCPY	:=	$(TOOLCHAIN_GNUBASE)objcopy
export OBJDMP	:=	$(TOOLCHAIN_GNUBASE)objdump
export RDELF	:=	$(TOOLCHAIN_GNUBASE)readelf