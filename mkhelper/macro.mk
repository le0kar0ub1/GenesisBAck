###############################################################################
##
##  This file is part of the GenesisBack project, and is made available under
##  the terms of the GNU General Public License version 3.
##
##  Copyright (C) 2020 - Leo Karoubi
##
###############################################################################

define CALLED_LOCAL_DIRECTORY
	$(strip $(dir $(realpath $(lastword $(MAKEFILE_LIST)))))
endef

# Fatal errors are raised here
define RAISE
	@echo -e "[$(BoldRed)ABORTED$(Blank)]$(1)"
	@exit 1
endef

# GenesisBack build-time log
define LOG
	@echo -e "[$(BoldBlue)$(PROJECT)$(Blank)]$(1)"
endef

# Is the toolchain built ?
define EvalFatToolChainExistence
	$(if $(filter $(PROJECT_PATH)/mktoolchain/toolchain, $(wildcard $(PROJECT_PATH)/mktoolchain/*)), $(call LOG, toolchain found at $(BoldMagenta)mktoolchain/toolchain$(Blank)), $(call RAISE, toolchain not built -- $(BoldRed)./mktoolchain/mktoolchain$(Blank)))
endef

# Is the tool in the toolchain ?
define EvalBinaryToolChainExistence
	$(if $(filter $(PROJECT_PATH)/mktoolchain/toolchain/bin/x86_64-elf-$(1), $(wildcard $(PROJECT_PATH)/mktoolchain/toolchain/bin/*)), $(call LOG, Toolchain tool found $(BoldMagenta)$(1)$(Blank)), $(call RAISE, Toolchain tool not found $(BoldRed)$(1)$(Blank)))
endef

# Is the binary present on the system ?
define EvalBinaryExistence
	$(if $(shell which $(1) 2> /dev/null),$(call LOG, Dependency found $(BoldMagenta)$(shell basename $(1))$(Blank)),$(call RAISE, Dependency not found $(BoldRed)$(shell basename $(1))$(Blank)))
endef

# Builder log action
define BUILD_LOG
	@echo "    $(1)target/$(shell basename $(TARGET_PATH))/$(subst $(TARGET_PATH)/,,$@)"
endef