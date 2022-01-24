# @author : eltertrias
# @brief : makefile for the execution subdirectory


# Variables
OUTPUT_DIR_EXECUTION = $(BUILD_DIR)/execution
OBJECTS += $(addprefix $(OUTPUT_DIR_EXECUTION)/, builtin.o env_variables.o)


# Rules
all_execution:
	mkdir -p $(OUTPUT_DIR_EXECUTION)

$(OUTPUT_DIR_EXECUTION)/%.o: execution/%.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: all_execution