# Root Makefile Example


# Variables
CC = gcc
LD = gcc
CFLAGS = -c -Wmissing-prototypes -Wshadow -Wall -Wextra -I include
LDFLAGS =
DEBUG_MODE = OFF# To turn debugging on, change OFF to ON

OBJECTS =
BUILD_DIR = build
PROGRAM_NAME = program

ifeq ("$(DEBUG_MODE)", "ON")
CFLAGS += -D DEBUG_MODE -g
endif


# Includes
include core/Makefile


# Make Rules
all: clean init_modules build

clean:
	rm -rf $(BUILD_DIR) *.o *.out
	mkdir -p $(BUILD_DIR)

init_modules: all_core

build: $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $(BUILD_DIR)/$(PROGRAM_NAME)


# Make config
.DEFAULT_GOAL = all
.PHONY: all clean build
