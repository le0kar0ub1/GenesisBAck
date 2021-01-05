###############################################################################
##
##  This file is part of the GenesisBack project, and is made available under
##  the terms of the GNU General Public License version 3.
##
##  Copyright (C) 2020 - Leo Karoubi
##
###############################################################################

sinclude mkhelper/def.mk
sinclude mkhelper/macro.mk
sinclude mkhelper/toolchain.mk

.PHONY: all
all: toolchain
	$(MAKE) -C src tgt=all

.PHONY: toolchain
toolchain:
	$(call EvalFatToolChainExistence)
	$(call EvalBinaryExistence,gcc)
	$(call EvalBinaryExistence,ld)

.PHONY: clean
clean:
	rm -rf $(TARGET_BASE_PATH)

.PHONY: re
re: clean all

.PHONY: run
run: all
	@$(TARGET_BASE_PATH)/debug/$(TARGET)

disassemble:
	@$(TOOLCHAIN_PATH)/bin/arm-tdmi-eabi-objdump --target=binary --architecture=armv4 -D res/Dragonball.gba

# Allow subdir targeted build - dev only
.PHONY: build
build:
	$(MAKE) -C src tgt=$(tgt)

.PHONY: doc
doc:
	doxygen doc/doxygen.cfg
