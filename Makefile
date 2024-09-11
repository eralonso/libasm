# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eralonso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/02 18:06:40 by eralonso          #+#    #+#              #
#    Updated: 2024/09/11 11:25:35 by eralonso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := asm

TESTS_PROGRAM_NAME := asm_tests

NAME_TYPE := library

ifeq ($(NAME_TYPE),library)
	NAME := $(addprefix lib,$(NAME))
	NAME := $(addsuffix .a,$(NAME))
endif

NULL := 
SPACE := $(NULL) #

SRCS_ROOT := src/
OBJS_ROOT := .obj/
DEPS_ROOT := .dep/
BIN_ROOT := bin/

TESTS_SRCS_ROOT := src/
TESTS_OBJS_ROOT := .obj/
TESTS_DEPS_ROOT := .dep/
TESTS_BIN_ROOT := bin/

SRCS_DIRS := ./
SRCS_DIRS := $(subst :,$(SPACE),$(SRCS_DIRS))
SRCS_DIRS := $(addprefix $(SRCS_ROOT),$(SRCS_DIRS))
SRCS_DIRS := $(subst $(SPACE),:,$(SRCS_DIRS))

TESTS_SRCS_DIRS := ./
TESTS_SRCS_DIRS := $(subst :,$(SPACE),$(TESTS_SRCS_DIRS))
TESTS_SRCS_DIRS := $(addprefix $(TESTS_SRCS_ROOT),$(TESTS_SRCS_DIRS))
TESTS_SRCS_DIRS := $(subst $(SPACE),:,$(TESTS_SRCS_DIRS))

FILES := ft_strlen ft_strcpy ft_strcmp ft_write ft_read \
		 ft_strdup convert_sign_to_number ft_strnchri \
		 ft_strchri is_sign_symbol convert_sign_str_n_to_number \
		 ft_isspace #ft_atoi_base

TESTS_FILES := main

SUFFIX := s

TESTS_SUFFIX := c

SRCS := $(addsuffix .$(SUFFIX),$(FILES))
OBJS := $(addprefix $(OBJS_ROOT),$(addsuffix .o,$(FILES)))
DEPS := $(addprefix $(DEPS_ROOT),$(addsuffix .d,$(FILES)))

TESTS_SRCS := $(addsuffix .$(TESTS_SUFFIX),$(TESTS_FILES))
TESTS_OBJS := $(addprefix $(TESTS_OBJS_ROOT),$(addsuffix .o,$(TESTS_FILES)))
TESTS_DEPS := $(addprefix $(TESTS_DEPS_ROOT),$(addsuffix .d,$(TESTS_FILES)))

ARFLAGS := Ucruvs

AS := nasm
ASFLAGS := -f elf64 -w+regsize
AS_MAKEFILE_DEPENDCY_FLAG := -MD

CFLAGS := -Wall -Wextra -Werror
ASAN_FLAGS := -fsanitize=address
DEBUG_FLAGS := -g
TESTS_DEPS_FLAGS := -MMD -MF

NAME := $(addprefix $(BIN_ROOT),$(NAME))
TESTS_PROGRAM_NAME := $(addprefix $(TESTS_BIN_ROOT),$(TESTS_PROGRAM_NAME))

TO_CREATE_DIRS := $(OBJS_ROOT) $(DEPS_ROOT) $(BIN_ROOT)

vpath %.$(SUFFIX) $(SRCS_DIRS)
vpath %.$(TESTS_SUFFIX) $(TESTS_SRCS_DIRS)
#vpath %.o $(OBJS_ROOT) $(TESTS_OBJS_ROOT)

#FUNCTIONS

define remove_dir_file
if ! [ -z $1 ]; then \
	$(RM) -r $1; \
else \
	$(RM) $2; \
fi
endef

#RULES

$(OBJS_ROOT)%.o: %.$(SUFFIX) $(OBJS_ROOT) $(DEPS_ROOT)
	$(AS) $(ASFLAGS) $(AS_MAKEFILE_DEPENDCY_FLAG) $(DEPS_ROOT)$(basename $*).d $< -o $@

$(TESTS_OBJS_ROOT)%.o: %.$(TESTS_SUFFIX) $(TESTS_OBJS_ROOT) $(TESTS_DEPS_ROOT)
	$(CC) -c $(CFLAGS) $(ASAN_FLAGS) $(DEBUG_FLAGS) $(TESTS_DEPS_FLAGS) $(TESTS_DEPS_ROOT)$(basename $*).d $< -o $@

all: $(NAME)

$(TO_CREATE_DIRS):
	-mkdir -p $@

$(NAME): $(BIN_ROOT)

ifeq ($(NAME_TYPE),executable)
$(NAME): $(OBJS)
	ld $(OBJS) -o $(NAME)
else ifeq ($(NAME_TYPE),library)
$(NAME): $(NAME)($(OBJS))
endif

tests: $(TESTS_PROGRAM_NAME)

$(TESTS_PROGRAM_NAME): $(TESTS_BIN_ROOT)

$(TESTS_PROGRAM_NAME): $(NAME) $(TESTS_OBJS)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $(DEBUG_FLAGS) $(TESTS_OBJS) $(NAME) -o $@

clean:
	$(call remove_dir_file,$(OBJS_ROOT),$(OBJS))
	$(call remove_dir_file,$(DEPS_ROOT),$(DEPS))
	$(call remove_dir_file,$(TESTS_OBJS_ROOT),$(TESTS_OBJS))
	$(call remove_dir_file,$(TESTS_DEPS_ROOT),$(TESTS_DEPS))

fclean: clean
	$(call remove_dir_file, $(BIN_ROOT),$(NAME))
	$(call remove_dir_file, $(TESTS_BIN_ROOT),$(TESTS_PROGRAM_NAME))

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re

.SECONDARY:
