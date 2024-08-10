# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eralonso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/02 18:06:40 by eralonso          #+#    #+#              #
#    Updated: 2024/08/10 10:02:52 by eralonso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := asm
NAME := $(addprefix lib,$(NAME))
NAME := $(addsuffix .a,$(NAME))

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

FILES := exit

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
if [ -d $1 ]; then \
	$(RM) -r $1; \
else \
	$(RM) $2; \
fi
endef

#RULES

$(OBJS_ROOT)%.o: %.$(SUFFIX)
	$(AS) $(ASFLAGS) $(AS_MAKEFILE_DEPENDCY_FLAG) $(DEPS_ROOT)$(basename $*).d $< -o $@

(%.o): $(OBJS_ROOT)%o

all: $(TO_CREATE_DIRS) $(NAME)

$(TO_CREATE_DIRS):
	-mkdir -p $@

$(NAME): $(NAME)($(OBJS))

#$(NAME): $(OBJS)
#	ld $(OBJS) -o $(NAME)

clean:
	$(call remove_dir_file,$(OBJS_ROOT),$(OBJS))
	$(call remove_dir_file,$(DEPS_ROOT),$(OBJS))

fclean: clean
	$(call remove_dir_file, $(BIN_ROOT),$(NAME))

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
.SECONDARY:
