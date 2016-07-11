# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/12 13:35:06 by bde-maze          #+#    #+#              #
#*   Updated: 2016/03/27 21:44:31 by bde-maze         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = $(shell ls -1 | grep "\.c")
OBJDIR = obj/

NO_COLOR = "\033[0;0m"
CC_COLOR = "\033[0;32m"
EX_COLOR = "\033[0;32m"
PX_COLOR = "\033[4;37m"
DE_COLOR = "\033[0;31m"

CC_STR = $(CC_COLOR)[OK]$(NO_COLOR)
EX_STR = $(EX_COLOR)$(NAME)$(NO_COLOR)
PX_STR = $(PX_COLOR)Library compiled successfully$(NO_COLOR)
DE_STR = $(DE_COLOR)Remove$(NO_COLOR)

OBJ = $(SRC:%.c=$(OBJDIR)%.o)

CC = clang

INC = -I ./includes

CFLAGS = -Wall -Werror -Wextra -g3

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $^
	@echo ""
	@echo $(PX_STR) : $(EX_STR)
	@echo ""

$(OBJDIR)%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) -c $(CFLAGS) $(INC) $< -o $@
	@echo $(CC_STR) $*

clean:
	@$(RM) $(OBJDIR)
	@echo $(DE_STR) objects

fclean: clean
	@$(RM) $(NAME)
	@echo $(DE_STR) $(NAME)

re: fclean all

.PHONNY: clean fclean re all
