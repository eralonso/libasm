# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eralonso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 16:02:53 by eralonso          #+#    #+#              #
#    Updated: 2025/01/27 17:06:13 by eralonso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libasm_killer

NULL := 
SPACE := $(NULL) #

SRCS_ROOT := src/
OBJS_ROOT := .obj/
DEPS_ROOT := .dep/
BIN_ROOT := bin/
INC_ROOT := inc/

SRCS_DIRS := ./:tests/:utils/
SRCS_DIRS := $(subst :,$(SPACE),$(SRCS_DIRS))
SRCS_DIRS := $(addprefix $(SRCS_ROOT),$(SRCS_DIRS))
SRCS_DIRS := $(subst $(SPACE),:,$(SRCS_DIRS))

INC_DIRS := $(INC_ROOT)

MAIN := main

TESTS := strlen strcpy strcmp write read \
		 #strdup convert_sign_to_number strnchri \
		 strchri is_sign_symbol convert_sign_str_n_to_number \
		 isspace str_n_find_first_not_of str_find_first_not_of \
		 has_char_duplicated str_has_min_size is_valid_base atoi_base \
		 create_elem list_push_front list_size list_swap_data \
		 list_at list_sort exit list_prev list_swap list_index \
		 list_del list_remove_if list_last list_push_back

UTILS := convcmp time typeconv

FILES := $(MAIN) $(TESTS) $(UTILS)


SUFFIX := c

SRCS := $(addsuffix .$(SUFFIX),$(FILES))
OBJS := $(addprefix $(OBJS_ROOT),$(addsuffix .o,$(FILES)))
DEPS := $(addprefix $(DEPS_ROOT),$(addsuffix .d,$(FILES)))

CFLAGS := -Wall -Wextra -Werror
ASAN_FLAGS := -fsanitize=address
DEBUG_FLAGS := -g
DEPS_FLAGS := -MMD -MF

NAME := $(addprefix $(BIN_ROOT),$(NAME))

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
	$(CC) -c $(CFLAGS) $(ASAN_FLAGS) $(DEBUG_FLAGS) $(INCLUDES) $(DEPS_FLAGS) $(DEPS_ROOT)$(basename $*).d $< -o $@

all: $(NAME)

$(TO_CREATE_DIRS):
	-mkdir -p $@

ifeq (,$(filter-out $(NAME),$(MAKECMDGOALS)))
ifndef LIBASM
	$(error LIBASM parameter is mandatory when using this rule)
endif
endif

$(NAME): $(BIN_ROOT)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $(DEBUG_FLAGS) $(OBJS) $(LIBASM) -o $@

clean:
	$(call remove_dir_file,$(OBJS_ROOT),$(OBJS))
	$(call remove_dir_file,$(DEPS_ROOT),$(DEPS))

fclean: clean
	$(call remove_dir_file, $(BIN_ROOT),$(NAME))

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re

.SILENT:
