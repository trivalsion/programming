# @author : eltertrias
# @brief : compiles utilities


CC = gcc
CFLAGS = -Wall -Wextra -I ../lib/include -c # c flags is needed as these are libraries that should be linked to other executables
BUILD_DIR = ../build/lib
OBJECTS = easyfilelib.o coreutils_library.o basics_lib.o


all: clean $(OBJECTS)

%.o : %.c
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$@

clean:
	rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)

.PHONY: all clean