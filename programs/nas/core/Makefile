# @author : eltertrias
# @brief : compiles the main part of the assembler



OUTPUT_DIR_CORE = $(BUILD_DIR)/core
OBJECTS += $(addprefix $(OUTPUT_DIR_CORE)/, parser.o main.o cli_arg_parser.o output_composer.o cleaner.o)



all_core:
	mkdir -p $(OUTPUT_DIR_CORE)

$(OUTPUT_DIR_CORE)/%.o : core/%.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: all_core