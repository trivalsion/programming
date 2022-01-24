# @author : eltertrias
# @brief : makefile for the core subdirectory


# Variables
OUTPUT_DIR_CORE = $(BUILD_DIR)/core
OBJECTS += $(addprefix $(OUTPUT_DIR_CORE)/, main.o common.o shell_cmd_arg_parser.o input_cleaner.o get_input.o interpreter.o parser.o)


# Rules
all_core:
	mkdir -p $(OUTPUT_DIR_CORE)

$(OUTPUT_DIR_CORE)/%.o: core/%.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: all_core