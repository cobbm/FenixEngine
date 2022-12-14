SRC_DIR := src
# OBJ_DIR := obj
# BIN_DIR := bin

TARGET = fenix
# OBJS = rendertarget.o

PSP_FW_VERSION = 550
BUILD_PRX = 1

COMMON_SRC := $(wildcard common/*.c)

FENIX_DIR := fenix
FENIX_SRC = $(wildcard $(FENIX_DIR)/src/*.cpp) 

SRC := $(wildcard $(SRC_DIR)/*.cpp) $(FENIX_SRC) $(COMMON_SRC) 
OBJS := $(SRC:%.cpp=%.o) 
OBJS := $(OBJS:%.c=%.o) $(FENIX_DIR)/src/font.c

INCDIR = $(FENIX_DIR)/src
CFLAGS = -G0 -Wall -std=c++17 -lstdc++ -lm -lpspmath 
# CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
CXXFLAGS = $(CFLAGS) -fno-exceptions
ASFLAGS = $(CFLAGS)

LIBDIR = 
LDFLAGS = 
LIBS = -lstdc++ -lpspgum_vfpu -lpspvfpu -lpspgu -lm -lpsprtc -lpspmath

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = FenixEngine Sample

# Set your pspdev directory:
PSPDEV := ~/pspdev/bin
PATH  := $(PATH):$(PSPDEV)
SHELL := env PATH=$(PATH) /bin/bash

PSPSDK=$(shell psp-config --pspsdk-path)


include $(PSPSDK)/lib/build.mak

$(FENIX_DIR)/src/font.c : $(FENIX_DIR)/src/font.raw
	bin2c $< $@ font

test:
	open /Applications/PPSSPPSDL.app --args "$(shell pwd)/EBOOT.PBP" 

upload:
	cp $(EXTRA_TARGETS) /Volumes/Untitled/PSP/GAME/fenix/

unmount:
	diskutil umountDisk /dev/disk4

