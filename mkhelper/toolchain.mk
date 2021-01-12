###############################################################################
##
##  This file is part of the GenesisBack project, and is made available under
##  the terms of the GNU General Public License version 3.
##
##  Copyright (C) 2020 - Leo Karoubi
##
###############################################################################

export TOOLCHAIN_PATH	 :=	$(PROJECT_PATH)/mktoolchain/toolchain
export TOOLCHAIN_GNUBASE := #$(TOOLCHAIN_PATH)/bin/$(ARCH)-elf-

ifeq ($(BUILD_MODE),release)
export TOOLCHAIN_INCLUDES	:=
export STATIC_LIBS			:=
export DYNAMIC_LIBS			:=
else
export TOOLCHAIN_INCLUDES	:=	$(TOOLCHAIN_PATH)/capstone/include # $(TOOLCHAIN_PATH)/readline
export STATIC_LIBS			:=	$(TOOLCHAIN_PATH)/capstone/libcapstone.a # $(TOOLCHAIN_PATH)/readline/libreadline.a
export DYNAMIC_LIBS			:=
endif

export CC		:=	$(TOOLCHAIN_GNUBASE)gcc
export AS		:=	$(TOOLCHAIN_GNUBASE)as
export AR		:=	$(TOOLCHAIN_GNUBASE)ar
export LD		:=	$(TOOLCHAIN_GNUBASE)ld
export OBJCPY	:=	$(TOOLCHAIN_GNUBASE)objcopy
export OBJDMP	:=	$(TOOLCHAIN_GNUBASE)objdump
export RDELF	:=	$(TOOLCHAIN_GNUBASE)readelf