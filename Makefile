# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eralonso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/02 18:06:40 by eralonso          #+#    #+#              #
#    Updated: 2024/08/05 13:03:24 by eralonso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := test

NULL := 
SPACE := $(NULL) #

SRCS_ROOT := src/
OBJS_ROOT := .obj/
BIN_ROOT := bin/

SRCS_DIRS := ./
SRCS_DIRS := $(subst :,$(SPACE),$(SRCS_DIRS))
SRCS_DIRS := $(addprefix $(SRCS_ROOT),$(SRCS_DIRS))
SRCS_DIRS := $(subst $(SPACE),:,$(SRCS_DIRS))

FILES := exit

SUFFIX := s

SRCS := $(addsuffix .$(SUFFIX),$(FILES)),
OBJS := $(addprefix $(OBJS_ROOT),$(addsuffix .o,$(FILES)))

AS := nasm
ASFLAGS := -f elf64
AS_MAKEFILE_DEPENDCY_FLAG := -MD

NAME := $(addprefix $(BIN_ROOT),$(NAME))
TO_CREATE_DIRS := $(OBJS_ROOT) $(BIN_ROOT)

vpath %.$(SUFFIX) $(SRCS_DIRS)

#FUNCTIONS

define remove_dir_file
ifneq ($1,)
	$(RM) -r $1
else
	$(RM) $2
endif
endef

#RULES

$(OBJS_ROOT)%.o: %.$(SUFFIX)
	$(AS) $(ASFLAGS) $(AS_MAKEFILE_DEPENDCY_FLAG) $(basename $*.$(DEP_SUFFIX)) $< -o $@

all: $(TO_CREATE_DIRS) $(NAME)

$(TO_CREATE_DIRS):
	-mkdir -p $@

$(NAME): $(OBJS)
	ld $(OBJS) -o $(NAME)

clean:
	$(eval $(call remove_dir_file,$(OBJS_ROOT),$(OBJS)))
#ifneq ($(OBJS_ROOT),)
#	$(RM) -r $(OBJS_ROOT)
#else
#	$(RM) $(OBJS)
#endif

fclean: clean
	$(eval $(call remove_dir_file, $(BIN_ROOT),$(NAME)))
#ifneq ($(BIN_ROOT),)
#	$(RM) -r $(BIN_ROOT)
#else
#	$(RM) $(NAME)
#endif

re: fclean all

hola/test.d patata:
	echo $@

.PHONY: all clean fclean re
