# @author : eltertrias
# @brief : compiles different binaries


CC = gcc
CFLAGS = -Wall -Wextra -I ../lib/include
BUILD_DIR = build
OBJECTS = eaddressbook.o efax.o psf2c.o conway_game_of_life.o #cat.o


all: clean $(OBJECTS)

%.o : %.c
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$@

clean:
	rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)

.PHONY: all clean