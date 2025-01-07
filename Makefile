PROJECT_NAME 	:= PhysicsEngine

# Toolchain
CPP = g++

# Directory structure
BUILD_DIR   	:= build
EXAMPLES_DIR	:= examples
OBJ_DIR     	:= $(BUILD_DIR)/obj
DEP_DIR     	:= $(BUILD_DIR)/dep
SRC_DIRS    	:= collisions/src core/src dynamics/src shapes/src world/src
INC_DIRS    	:= collisions/inc core/inc dynamics/inc shapes/inc world/inc

example 		?= basic_render
MAIN_DIR     	:= $(EXAMPLES_DIR)/$(example)

# Compiler and linker flags
WARNINGS     	:= -Wall -Wextra -Werror
COMMON_FLAGS 	:= $(WARNINGS) -nostdlib -nostartfiles -ffreestanding -mgeneral-regs-only -msse
C_FLAGS      	:= $(COMMON_FLAGS) $(addprefix -I,$(INC_DIRS))
CPP_FLAGS    	:= $(COMMON_FLAGS) $(addprefix -I,$(INC_DIRS))


# Find all source files
CPP_SRCS   := $(shell find $(SRC_DIRS) -name '*.cc')

CPP_SRCS += $(shell find $(MAIN_DIR) -name '*.cc')

# Generate object file names
CPP_OBJS   := $(CPP_SRCS:%.cc=$(OBJ_DIR)/%_cc.o)
ALL_OBJS   := $(CPP_OBJS)

# Generate dependency file names
DEP_FILES := $(ALL_OBJS:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

all: directories $(BUILD_DIR)/$(PROJECT_NAME)

directories:
	@mkdir -p $(BUILD_DIR) $(OBJ_DIR) $(DEP_DIR) \
		$(addprefix $(OBJ_DIR)/,$(SRC_DIRS)) \
		$(addprefix $(DEP_DIR)/,$(SRC_DIRS))

$(OBJ_DIR)/%_cc.o: %.cc
	@echo "Compiling $<..."
	@mkdir -p $(dir $@) $(dir $(DEP_DIR)/$*_cc.d)
	@$(CPP) $(CPP_FLAGS) -MMD -MF $(DEP_DIR)/$*_cc.d -c $< -o $@

$(BUILD_DIR)/$(PROJECT_NAME): $(ALL_OBJS)
	@echo "Building Physics Engine..."
	@$(CPP) $(ALL_OBJS) -o $(BUILD_DIR)/$(PROJECT_NAME)
	@echo "Building Physics Engine complete"
	@echo ""

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)
	@echo "Clean complete"

doxygen:
	@echo "Generating documentation..."
	@doxygen doxygen/Doxyfile
	@echo "Documentation generated"

format:
	@echo "Formatting files..."
	@find . -type f \( -name "*.cc" -o -name "*.h" -o -name "*.c" \) -exec clang-format -i -style=file {} +

help:
	@echo "Available targets:"
	@echo "  all      		 - Build the kernel image"
	@echo "  doxygen   		 - Generate an HTML documentation website"
	@echo "  clean    		 - Remove build directory"
	@echo "  format   		 - Format source files using clang-format"
	@echo "Inputs:"
	@echo "  example 	     - Input as relative path to examples directory (ie: 'basic_render')"

-include $(DEP_FILES)

.PHONY: all clean directories format help doxygen