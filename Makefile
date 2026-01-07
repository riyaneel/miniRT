# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/05 12:10:50 by rel-qoqu          #+#    #+#              #
#    Updated: 2026/01/06 18:50:56 by rel-qoqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project
NAME			:= miniRT
DEBUG_NAME		:= $(NAME)_debug

# Compiler and tools
C_COMPILER		:= cc
CXX_COMPILER	:= c++
MKDIR			:= mkdir -p
RMF				:= rm -f
RMD				:= rm -rf
NORMI			:= norminette

# Directories
SOURCE_DIR		:= src
INCLUDE_DIR		:= include
LIB_DIR			:= lib
TEST_DIR		:= test
BUILD_DIR		:= build
RT_DIR			:= $(BUILD_DIR)/rt
REL_RT_DIR		:= $(RT_DIR)/release
DBG_RT_DIR		:= $(RT_DIR)/debug
ASM_DIR			:= $(BUILD_DIR)/asm
REL_ASM_DIR		:= $(ASM_DIR)/release
DBG_ASM_DIR		:= $(ASM_DIR)/debug

# Flags
WARN_FLAGS		:= -Wall -Wextra -Werror -Wshadow -Wformat=2 -Winline \
					-Wsign-conversion -Wconversion -Wcast-align -Wcast-qual \
					-Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations \
					-Wold-style-definition -Wundef -Wnull-dereference -Wuninitialized \
					-Wwrite-strings -Wpadded -Wdouble-promotion -Wvla -pedantic \
					-Wfloat-equal
POSIX_FLAGS			:= -D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=200809L
DEPENDENCIES_FLAGS	:= -MMD -MP
SECURE_FLAGS		:= -fstack-protector-strong
INCLUDE_FLAGS		:= -I$(INCLUDE_DIR)

LTO_FLAGS			:= -flto
SAN_FLAGS			:= -fsanitize=address,undefined

C_FLAGS				:= $(WARN_FLAGS) $(POSIX_FLAGS) $(SECURE_FLAGS) $(DEPENDENCIES_FLAGS) \
						$(INCLUDE_FLAGS) -std=c11 -march=native
C_RELEASE_FLAGS		:= $(C_FLAGS) -O3 -fwrapv -ffast-math
LD_RELEASE_FLAGS	:= $(LTO_FLAGS)

C_DEBUG_FLAGS		:= $(C_FLAGS) -Og -g3 -DDEBUG -ftrapv
LD_DEBUG_FLAGS		:= $(LTO_FLAGS) $(SAN_FLAGS)

# Files
ALLOCATOR_FILES		:= $(addprefix allocator/, arena_alloc.c arena_alloc_align.c \
						arena_alloc_array.c arena_begin_tmp.c arena_create.c \
						arena_destroy.c arena_end_tmp.c arena_get_capacity.c \
						arena_get_used.c arena_reset.c)
CORE_FILES			:= $(addprefix core/, core_init.c)
SOURCE_FILES		:= $(ALLOCATOR_FILES) $(CORE_FILES) main.c
SOURCES				:= $(addprefix $(SOURCE_DIR)/, $(SOURCE_FILES))

OBJS_RELEASE	:= $(patsubst $(SOURCE_DIR)/%.c, $(REL_RT_DIR)/%.o, $(SOURCES))
OBJS_DEBUG		:= $(patsubst $(SOURCE_DIR)/%.c, $(DBG_RT_DIR)/%.o, $(SOURCES))

DEPS_RELEASE	:= $(OBJS_RELEASE:.o=.d)
DEPS_DEBUG		:= $(OBJS_DEBUG:.o=.d)

ASMS_RELEASE	:= $(patsubst $(SOURCE_DIR)/%.c, $(REL_ASM_DIR)/%.s, $(SOURCES))
ASMS_DEBUG		:= $(patsubst $(SOURCE_DIR)/%.c, $(DBG_ASM_DIR)/%.s, $(SOURCES))

DEPS_REL_ASM	:= $(ASMS_RELEASE:.s=.d)
DEPS_DBG_ASM	:= $(ASMS_DEBUG:.s=.d)

# Build rules
all: $(NAME)

$(NAME): $(OBJS_RELEASE)
	@printf "[\033[33mLinking\033[0m]   %-35s\n" "$@"
	@$(C_COMPILER) $(LD_RELEASE_FLAGS) $^ -o $@

$(REL_RT_DIR)/%.o: $(SOURCE_DIR)/%.c
	@$(MKDIR) $(@D)
	@printf "[\033[32mCompiling\033[0m] %-35s\n" "$< (release)"
	@$(C_COMPILER) $(C_RELEASE_FLAGS) $(LTO_FLAGS) -c $< -o $@
	@printf "\033[K"

release_asm: $(ASMS_RELEASE)

$(REL_ASM_DIR)/%.s: $(SOURCE_DIR)/%.c
	@$(MKDIR) $(@D)
	@printf "[\033[36mGenerating ASM\033[0m] %-35s\n" "$< (release)"
	@$(C_COMPILER) $(C_RELEASE_FLAGS) -S $< -o $@
	@printf "\033[K"

debug: $(DEBUG_NAME)

$(DEBUG_NAME): $(OBJS_DEBUG)
	@printf "[\033[33mLinking\033[0m]   %-35s\n" "$@"
	@$(C_COMPILER) $(LD_DEBUG_FLAGS) $^ -o $@

$(DBG_RT_DIR)/%.o: $(SOURCE_DIR)/%.c
	@$(MKDIR) $(@D)
	@printf "[\033[32mCompiling\033[0m] %-35s\n" "$< (debug)"
	@$(C_COMPILER) $(C_DEBUG_FLAGS) $(LTO_FLAGS) $(SAN_FLAGS) -c $< -o $@
	@printf "\033[K"

debug_asm: $(ASMS_DEBUG)

$(DBG_ASM_DIR)/%.s: $(SOURCE_DIR)/%.c
	@$(MKDIR) $(@D)
	@printf "[\033[36mGenerating ASM\033[0m] %-35s\n" "$< (debug)"
	@$(C_COMPILER) $(C_DEBUG_FLAGS) -S $< -o $@
	@printf "\033[K"

clean:
	@printf "Removing build artefacts...\n"
	@$(RMD) $(BUILD_DIR)
	@printf "Build artefacts removed.\n"

fclean: clean
	@printf "Removing executables...\n"
	@$(RMF) $(NAME) $(DEBUG_NAME)
	@printf "Executables removed.\n"

re: fclean all

# Help and debug rules
define AWK_NORM
BEGIN { \
    RED="\033[31m"; \
    RESET="\033[0m"; \
} \
!/OK!$$/ { printf RED"%s"RESET"\n", $$0 }
endef

norm:
	@tmp_output=$$(mktemp); \
	$(NORMI) $(INCLUDE_DIR) $(SOURCES) > $$tmp_output 2>&1; norm_status=$$? || true; \
	awk '$(AWK_NORM)' < $$tmp_output; \
	rm $$tmp_output; \
	if [ $$norm_status -eq 0 ]; then \
		printf "\033[32mNorminette check successful.\033[0m\n"; \
	else \
		printf "\033[31mNorminette check found issues.\033[0m\n"; \
		exit 1; \
	fi

# Phony and deps
.PHONY: all release_asm debug debug_asm clean fclean re norm

-include $(DEPS_RELEASE) $(DEPS_DEBUG)

.SUFFIXES: