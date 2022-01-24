# @author : eltertrias
# @brief : root makefile of the universal assembler



PROGRAM_NAME = nas
ARCH_DIR = arch
ARCH = chip8
ARCH_CONFIG = arch/$(ARCH)/include/

CC = gcc
LD = gcc
CFLAGS = -Wmissing-prototypes -Wshadow -Wall -Wextra -c -I include -I $(ARCH_CONFIG) # the parser source code needs defenitions that are specific to each arch, while parser is same for all. So parser source includes an asm-config.h file, and the build system just adds the arch include dirctory during compilation, and so depending on the arch, the arch include directory will change and so will asm-config.h file change(the one included would be from a different directory each time)
LDFLAGS =
DEBUG_MODE = OFF

ifeq ("$(DEBUG_MODE)", "ON")
CFLAGS += -D DEBUG_MODE
endif

BUILD_DIR = build
OBJECTS =



include $(ARCH_DIR)/$(ARCH)/Makefile
include core/Makefile



all: clean all_$(ARCH) all_core build

build: $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $(BUILD_DIR)/$(PROGRAM_NAME)

test:
	@echo "-------------- Memory Leak Test --------------" # @ means that the command would not be outputed(but it's result will still be outputed) when the makefile is ran
	valgrind $(BUILD_DIR)/$(PROGRAM_NAME) test/test-program.s
	@echo " " # Add a blank line after output

	@echo "-------------- Cleaner test --------------"
	$(BUILD_DIR)/$(PROGRAM_NAME) test/cleaner-parser-test.s
	@echo " "

	@echo "-------------- Output test --------------"
	$(BUILD_DIR)/$(PROGRAM_NAME) test/output-test.s
	@echo " "

	@echo "-------------- Test program --------------"
	$(BUILD_DIR)/$(PROGRAM_NAME) test/test-program.s
	@echo " "

clean:
	rm -rf $(BUILD_DIR)
	rm -rf test/*.o

	mkdir -p $(BUILD_DIR)

.PHONY: all clean build test
.DEFAULT_GOAL = all
