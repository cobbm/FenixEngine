SRC_DIR := src
# OBJ_DIR := obj
# BIN_DIR := bin

TARGET = pspmathdebug
# OBJS = rendertarget.o

PSP_FW_VERSION = 550
# BUILD_PRX = 1

COMMON_SRC := $(wildcard ../common/*.c)

SRC := $(wildcard $(SRC_DIR)/*.cpp) $(COMMON_SRC) 
OBJS := $(SRC:%.cpp=%.o) 
OBJS := $(OBJS:%.c=%.o) 

INCDIR = 

CFLAGS = -G0 -Wall -std=c++17 -lstdc++ -lm -lpspmath
# CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
CXXFLAGS = $(CFLAGS) -fno-exceptions
ASFLAGS = $(CFLAGS)

LIBDIR = 
LDFLAGS = 
LIBS = -lstdc++ -lpspgum_vfpu -lpspgu -lm -lpsprtc -lpspmath

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = pspmath debug

# Set your pspdev directory:
PSPDEV := ~/pspdev/bin
PATH  := $(PATH):$(PSPDEV)
SHELL := env PATH=$(PATH) /bin/bash

PSPSDK=$(shell psp-config --pspsdk-path)


include $(PSPSDK)/lib/build.mak

test:
	open -n /Applications/PPSSPPSDL.app --args "$(shell pwd)/EBOOT.PBP" 

upload:
	cp $(EXTRA_TARGETS) /Volumes/Untitled/PSP/GAME/pspmath/

unmount:
	diskutil umountDisk /dev/disk4

