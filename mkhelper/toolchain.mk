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

export TOOLCHAIN_INCLUDES           =   $(TOOLCHAIN_PATH)/sdl2/include      \
                                        $(TOOLCHAIN_PATH)/sdl2_ttf          \
                                        $(TOOLCHAIN_PATH)/sdl2_image
export TOOLCHAIN_INLINE_MACRO       =   # -D SDL_FONT_PATH="$(TOOLCHAIN_PATH)/sdl2_ttf"
export TOOLCHAIN_STATIC_LIBS 		= 
export TOOLCHAIN_DYNAMIC_LIBS_AREA  =   $(TOOLCHAIN_PATH)/sdl2/build/.libs    \
                                        $(TOOLCHAIN_PATH)/sdl2_ttf/.libs      \
                                        $(TOOLCHAIN_PATH)/sdl2_image/.libs
export TOOLCHAIN_DYNAMIC_LIBS       =   SDL2                                   \
                                        SDL2_ttf                               \
                                        SDL2_image

ifeq ($(BUILD_MODE),release)
    TOOLCHAIN_INCLUDES	         +=
    TOOLCHAIN_STATIC_LIBS	     +=
    TOOLCHAIN_DYNAMIC_LIBS_AREA  +=
    TOOLCHAIN_DYNAMIC_LIBS		 +=
    TOOLCHAIN_INLINE_MACRO       +=
else
    TOOLCHAIN_INCLUDES	        +=	$(TOOLCHAIN_PATH)/capstone/include
    TOOLCHAIN_STATIC_LIBS		+=
    TOOLCHAIN_DYNAMIC_LIBS_AREA +=  $(TOOLCHAIN_PATH)/capstone
    TOOLCHAIN_DYNAMIC_LIBS		+=  capstone
    TOOLCHAIN_INLINE_MACRO      +=
endif

export CC		:=	$(TOOLCHAIN_GNUBASE)gcc
export AS		:=	$(TOOLCHAIN_GNUBASE)as
export AR		:=	$(TOOLCHAIN_GNUBASE)ar
export LD		:=	$(TOOLCHAIN_GNUBASE)ld
export OBJCPY	:=	$(TOOLCHAIN_GNUBASE)objcopy
export OBJDMP	:=	$(TOOLCHAIN_GNUBASE)objdump
export RDELF	:=	$(TOOLCHAIN_GNUBASE)readelf