# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eralonso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/02 18:06:40 by eralonso          #+#    #+#              #
#    Updated: 2024/09/05 08:38:39 by eralonso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := asm

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

SRCS_DIRS := ./
SRCS_DIRS := $(subst :,$(SPACE),$(SRCS_DIRS))
SRCS_DIRS := $(addprefix $(SRCS_ROOT),$(SRCS_DIRS))
SRCS_DIRS := $(subst $(SPACE),:,$(SRCS_DIRS))

FILES := ft_strlen ft_strcpy ft_strcmp ft_write ft_read \
		 ft_strdup convert_sign_to_number ft_strchri \
		 is_sign_symbol #convert_sign_str_n_to_number #ft_atoi_base

SUFFIX := s

SRCS := $(addsuffix .$(SUFFIX),$(FILES)),
OBJS := $(addprefix $(OBJS_ROOT),$(addsuffix .o,$(FILES)))
DEPS := $(addprefix $(DEPS_ROOT),$(addsuffix .d,$(FILES)))

AS := nasm
ASFLAGS := -f elf64
AS_MAKEFILE_DEPENDCY_FLAG := -MD

NAME := $(addprefix $(BIN_ROOT),$(NAME))
TO_CREATE_DIRS := $(OBJS_ROOT) $(DEPS_ROOT) $(BIN_ROOT)

vpath %.$(SUFFIX) $(SRCS_DIRS)
vpath %.o $(OBJS_ROOT)

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

clean:
	$(call remove_dir_file,$(OBJS_ROOT),$(OBJS))
	$(call remove_dir_file,$(DEPS_ROOT),$(OBJS))

fclean: clean
	$(call remove_dir_file, $(BIN_ROOT),$(NAME))

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
.SECONDARY:
