###############################################################################
##
##  This file is part of the GenesisBack project, and is made available under
##  the terms of the GNU General Public License version 3.
##
##  Copyright (C) 2020 - Leo Karoubi
##
###############################################################################

sinclude $(PROJECT_PATH)/mkhelper/macro.mk
sinclude $(PROJECT_PATH)/mkhelper/toolchain.mk

# Build directory, defaulting to debug
ifeq ($(BUILD_MODE),release)
    TARGET_PATH		:= $(TARGET_BASE_PATH)/release
    CCFLAGS			+= -D ROUTINE=ROUTINE_RELEASE
else
    TARGET_PATH		:= $(TARGET_BASE_PATH)/debug
    CCFLAGS			+= -D ROUTINE=ROUTINE_DEBUG
endif

TARGET_OBJECTS 	:=	$(PROJECT_PATH)/src/main.o

ifeq ($(tgt),all)
	ifeq ($(BUILD_MODE),release)
		sinclude $(PROJECT_PATH)/src/core/Makefile
	else
		sinclude $(PROJECT_PATH)/src/core/Makefile
		sinclude $(PROJECT_PATH)/src/debug/Makefile
	endif
	sinclude $(PROJECT_PATH)/src/modules/Makefile
	sinclude $(PROJECT_PATH)/src/mmu/Makefile
	sinclude $(PROJECT_PATH)/src/gba/Makefile
else
	ifeq ($(shell test -e $(PROJECT_PATH)/src/$(tgt)/main.c && echo -n found),found)
		sinclude $(PROJECT_PATH)/src/$(tgt)/Makefile
		TARGET_OBJECTS += $(PROJECT_PATH)/src/$(tgt)/main.o
	endif
endif

TARGET_OBJECTS	:=	$(patsubst $(PROJECT_PATH)%, $(TARGET_PATH)%, $(TARGET_OBJECTS))
TARGET_DEPS		:= 	$(TARGET_OBJECTS:.o=.d)

.PHONY: all
all: toolchaindebug $(TARGET_OBJECTS) $(TARGET)

toolchaindebug:
ifeq ($(BUILD_MODE),release)
else
	$(call EvalFatToolChainExistence)
endif

$(TARGET):	$(TARGET_OBJECTS)
	$(CC) $(TARGET_OBJECTS) $(LDFLAGS) -o $(TARGET_PATH)/$(TARGET)
	$(call BUILD_LOG,[LD]     )

-include $(TARGET_DEPS)
$(TARGET_PATH)%$(EXTENSION_OBJ): $(PROJECT_PATH)%$(EXTENSION_CC)
	mkdir -p $(shell dirname $@)
	$(CC) $(CCFLAGS) -c $< -o $@
	$(call BUILD_LOG,[CC]     )
