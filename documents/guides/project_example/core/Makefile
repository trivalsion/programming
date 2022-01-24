# Submakefile example


# Variables
OUTPUT_DIR_core = $(BUILD_DIR)/core
OBJECTS += $(addprefix $(OUTPUT_DIR_core)/, file.o)


# Rules
all_core:
	mkdir -p $(OUTPUT_DIR_core)

$(OUTPUT_DIR_core)/%.o: core/%.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: all_core