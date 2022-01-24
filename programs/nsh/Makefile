# @author : eltertrias
# @brief : the main root makefile of the nSH project


# Variables
CC = gcc
LD = gcc
CFLAGS = -c -Wmissing-prototypes -Wshadow -Wall -Wextra -I include
LDFLAGS =
DEBUG_MODE = OFF# To turn debugging on, change OFF to ON

OBJECTS =
BUILD_DIR = build
PROGRAM_NAME = nsh

ifeq ("$(DEBUG_MODE)", "ON")
CFLAGS += -D DEBUG_MODE -g
endif


# Includes
include core/Makefile
include execution/Makefile


# Make Rules
all: clean init_modules build

clean:
	rm -rf build *.o *.so *.out
	mkdir -p build

init_modules: all_core all_execution

build: $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $(BUILD_DIR)/$(PROGRAM_NAME)

test:
	@echo "-------------- Memory Leak Test --------------" # @ means that the command would not be outputed(but it's result will still be outputed) when the makefile is ran
	valgrind $(BUILD_DIR)/$(PROGRAM_NAME)


# Make config
.DEFAULT_GOAL = all
.PHONY: clean, all, build