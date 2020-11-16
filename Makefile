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
	$(MAKE) -C src

.PHONY: toolchain
toolchain:
	$(call EvalFatToolChainExistence)
	$(call EvalBinaryToolChainExistence,gcc)
	$(call EvalBinaryToolChainExistence,ld)

.PHONY: clean
clean:
	rm -rf $(TARGET_BASE_PATH)

.PHONY: re
re: clean all

# ifeq ($(debug),soft)
# endif

.PHONY: run
run: all