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

export TOOLCHAIN_INCLUDES = $(TOOLCHAIN_PATH)/sdl2/include
export STATIC_LIBS 		  = 
export DYNAMIC_LIBS_AREA  = $(TOOLCHAIN_PATH)/sdl2/build/.libs
export DYNAMIC_LIBS       = SDL2

ifeq ($(BUILD_MODE),release)
    TOOLCHAIN_INCLUDES	+=
    STATIC_LIBS			+=
    DYNAMIC_LIBS_AREA   +=
    DYNAMIC_LIBS		+=
else
    TOOLCHAIN_INCLUDES	+=	$(TOOLCHAIN_PATH)/capstone/include # $(TOOLCHAIN_PATH)/readline
    STATIC_LIBS			+=	$(TOOLCHAIN_PATH)/capstone/libcapstone.a # $(TOOLCHAIN_PATH)/readline/libreadline.a
    DYNAMIC_LIBS_AREA   +=
    DYNAMIC_LIBS		+=
endif

export CC		:=	$(TOOLCHAIN_GNUBASE)gcc
export AS		:=	$(TOOLCHAIN_GNUBASE)as
export AR		:=	$(TOOLCHAIN_GNUBASE)ar
export LD		:=	$(TOOLCHAIN_GNUBASE)ld
export OBJCPY	:=	$(TOOLCHAIN_GNUBASE)objcopy
export OBJDMP	:=	$(TOOLCHAIN_GNUBASE)objdump
export RDELF	:=	$(TOOLCHAIN_GNUBASE)readelf