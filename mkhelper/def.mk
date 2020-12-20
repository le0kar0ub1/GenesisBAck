###############################################################################
##
##  This file is part of the GenesisBack project, and is made available under
##  the terms of the GNU General Public License version 3.
##
##  Copyright (C) 2020 - Leo Karoubi
##
###############################################################################

export PROJECT		:= GenesisBack
export PROJECT_PATH	:= $(realpath .)

# Target architecture
export ARCH ?= $(shell $(CC) -dumpmachine | cut -d '-' -f 1)

# Build config
cfg ?= debug
export BUILD_MODE = $(cfg)

# Make verbosity
export MAKEFLAGS += --no-print-directory --silent

# File extension norm
export EXTENSION_BIN	:=	bin
export EXTENSION_ISO	:=	iso
export EXTENSION_CC		:=	.c
export EXTENSION_OBJ	:=	.o
export EXTENSION_LIB	:=	.a

# Versionning
export VERSION			:=	0.1.0

# Target
export TARGET_BASE_PATH	:=	$(PROJECT_PATH)/target

# Build target
export TARGET	:=	$(PROJECT)-$(VERSION).$(EXTENSION_BIN)

# Cleaner as possible
export CCFLAGS	=	-I $(PROJECT_PATH)/inc						\
					-Wall										\
					-MD											\
					-Wcast-align					    		\
					-Wextra				 						\
					-Wnested-externs							\
					-Winline									\
					-Wpragmas									\
					-std=gnu11									\
					-Wuninitialized								\
					-Wno-missing-braces							\
					-Wcast-align								\
					-Wwrite-strings								\
					-Wparentheses								\
					-Wunreachable-code							\
					-Wno-unused									\
					-Wmissing-field-initializers				\
					-Wswitch-enum								\
					-Wshadow				 					\
					-Wuninitialized				 				\
					-Wmissing-declarations						\
					-Wmissing-prototypes						\
					-Wstrict-prototypes							\
					-Wpointer-arith								\
					-fms-extensions 							\
					-fno-tree-loop-vectorize 					\
					-fno-tree-slp-vectorize						\
					-Wno-override-init							\

# Some macros
export CCFLAGS	+=	-D PROJECT=$(PROJECT)							\
					-D COMPILER_VERSION=$(shell $(CC) -dumpversion)	\
					-D PROJECT_VERSION=$(VERSION)					\
					-D ARCH=$(ARCH)									\

export LDFLAGS	:=	

# Output color
export Red			:= \e[0;31m
export BoldRed		:= \e[1;31m
export Green		:= \e[0;32m
export BoldGreen	:= \e[1;32m
export Yellow		:= \e[0;33m
export BoldYellow	:= \e[1;33m
export Blue			:= \e[0;34m
export BoldBlue		:= \e[1;34m
export Magenta		:= \e[0;35m
export BoldMagenta 	:= \e[1;35m
export Cyan			:= \e[0;36m
export BoldCyan		:= \e[1;36m
export Blank		:= \e[0m
