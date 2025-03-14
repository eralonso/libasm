# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eralonso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/02 18:06:40 by eralonso          #+#    #+#              #
#    Updated: 2025/01/27 16:56:01 by eralonso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ORIGIN_NAME := asm
NAME := asm
TESTER := $(addsuffix _killer, $(NAME))

NAME_TYPE := library

ifeq ($(NAME_TYPE),library)
	NAME := $(addprefix lib,$(NAME))
	NAME := $(addsuffix .a,$(NAME))
	TESTER := $(addprefix lib,$(TESTER))
endif


NULL := 
SPACE := $(NULL) #

SRCS_ROOT := src/
OBJS_ROOT := .obj/
DEPS_ROOT := .dep/
BIN_ROOT := bin/
INC_ROOT := inc/
TEST_ROOT := test/

SRCS_DIRS := ./
SRCS_DIRS := $(subst :,$(SPACE),$(SRCS_DIRS))
SRCS_DIRS := $(addprefix $(SRCS_ROOT),$(SRCS_DIRS))
SRCS_DIRS := $(subst $(SPACE),:,$(SRCS_DIRS))

INC_DIRS := $(INC_ROOT)

FILES := ft_strlen ft_strcpy ft_strcmp ft_write ft_read \
		 ft_strdup convert_sign_to_number ft_strnchri \
		 ft_strchri is_sign_symbol convert_sign_str_n_to_number \
		 ft_isspace str_n_find_first_not_of str_find_first_not_of \
		 has_char_duplicated str_has_min_size is_valid_base ft_atoi_base \
		 ft_create_elem ft_list_push_front ft_list_size ft_list_swap_data \
		 ft_list_at ft_list_sort ft_exit ft_list_prev ft_list_swap ft_list_index \
		 ft_list_del ft_list_remove_if ft_list_last ft_list_push_back

SUFFIX := s

SRCS := $(addsuffix .$(SUFFIX),$(FILES))
OBJS := $(addprefix $(OBJS_ROOT),$(addsuffix .o,$(FILES)))
DEPS := $(addprefix $(DEPS_ROOT),$(addsuffix .d,$(FILES)))

ARFLAGS := Ucruvs

AS := nasm
ASFLAGS := -f elf64 #-w+regsize -w+label-orphan # <- These flags are set by default
AS_MAKEFILE_DEPENDCY_FLAG := -MD

NAME := $(addprefix $(BIN_ROOT),$(NAME))
TESTER := $(addprefix $(BIN_ROOT),$(TESTER))

TO_CREATE_DIRS := $(OBJS_ROOT) $(DEPS_ROOT) $(BIN_ROOT)

INCLUDES := $(addprefix -I,$(INC_DIRS))

vpath %.$(SUFFIX) $(SRCS_DIRS)

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
	$(AS) $(ASFLAGS) $(AS_MAKEFILE_DEPENDCY_FLAG) $(DEPS_ROOT)$(basename $*).d $(INCLUDES) $< -o $@

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

$(TESTER): $(NAME)
	$(MAKE) -C $(TEST_ROOT) LIBASM="$(shell pwd)/$(NAME)"
	mv $(TEST_ROOT)$(TESTER) $(TESTER)

tests: $(TESTER)
	echo "\n"
	$<

clean:
	$(call remove_dir_file,$(OBJS_ROOT),$(OBJS))
	$(call remove_dir_file,$(DEPS_ROOT),$(DEPS))

fclean: clean
	$(call remove_dir_file, $(BIN_ROOT),$(NAME))
	$(MAKE) -C $(TEST_ROOT) clean

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re tests $(TESTER)

.SECONDARY:

.SILENT: tests $(TESTER)
