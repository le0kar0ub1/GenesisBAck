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
else
    TARGET_PATH		:= $(TARGET_BASE_PATH)/debug
    CCFLAGS			+= #-g3
endif

TARGET_OBJECTS :=

ifeq ($(tgt),all)
sinclude $(PROJECT_PATH)/src/machine/Makefile
sinclude $(PROJECT_PATH)/src/emulator/Makefile
sinclude $(PROJECT_PATH)/src/isa/Makefile
else
ifeq ($(shell test -e $(PROJECT_PATH)/src/$(tgt)/main.c && echo -n found),found)
sinclude $(PROJECT_PATH)/src/$(tgt)/Makefile
TARGET_OBJECTS += $(PROJECT_PATH)/src/$(tgt)/main.o
endif
endif

TARGET_OBJECTS	:=	$(patsubst $(PROJECT_PATH)%, $(TARGET_PATH)%, $(TARGET_OBJECTS))
TARGET_DEPS		:= 	$(TARGET_OBJECTS:.o=.d)

.PHONY: all
all: $(TARGET_OBJECTS) $(TARGET)

$(TARGET):	$(TARGET_OBJECTS)
	$(CC) $(TARGET_OBJECTS) $(LDFLAGS) -o $(TARGET_PATH)/$(TARGET)
	$(call BUILD_LOG,[LD]     )

-include $(TARGET_DEPS)
$(TARGET_PATH)%$(EXTENSION_OBJ): $(PROJECT_PATH)%$(EXTENSION_CC)
	mkdir -p $(shell dirname $@)
	$(CC) $(CCFLAGS) -c $< -o $@
	$(call BUILD_LOG,[CC]     )
