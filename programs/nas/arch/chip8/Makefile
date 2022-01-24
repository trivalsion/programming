# @author : eltertrias
# @brief : a makefile to compile stuff for the chip



OUTPUT_DIR_CHIP8 = $(BUILD_DIR)/$(ARCH)
OBJECTS += $(addprefix $(OUTPUT_DIR_CHIP8)/, chip8.o)



all_$(ARCH):
	mkdir -p $(OUTPUT_DIR_CHIP8)

$(OUTPUT_DIR_CHIP8)/%.o : $(ARCH_DIR)/$(ARCH)/%.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: all_$(ARCH)