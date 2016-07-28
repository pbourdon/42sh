# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/02 13:52:37 by bde-maze          #+#    #+#              #
#    Updated: 2016/07/23 18:43:01 by cmichaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

HEADER = includes/minishell.h

FLAGS = -Wall -Werror -Wextra -g3 -O3

LIBFLAGS = -lncurses

SRC = 	main.c \
		cd.c \
		cd2.c \
		cd3.c \
		env.c \
		env2.c \
		env3.c \
		parseandexc.c \
		parseandexc2.c \
		setenv.c \
		setenv2.c \
		tools.c \
		tools2.c \
		unsetenv.c \
		allwrites.c \
		spliter.c \
		split_on_spec.c \
		error.c \
		to_treetest.c \
		good_order.c \
		arg_to_list.c

OBJDIR = obj/

OBJ = $(SRC:%.c=$(OBJDIR)%.o)

all: $(NAME)

norm:
	@norminette $(SRC) $(HEADER)

$(NAME): compile_lib compile_p $(OBJ)
		@clang $(FLAGS) $(LIBFLAGS) -o $(NAME) $(OBJ) -L libft -lft
		@echo ""
		@echo "\033[32mCompilation Succeeded\033[39m"
		@echo ""

compile_p:
		@echo "\n\033[34mCompiling Project Wait...\033[39m"
		@echo ""

compile_lib:
		@make -C libft/

$(OBJDIR)%.o: %.c
		@mkdir -p $(OBJDIR)
		@clang $(FLAGS) -I libft/includes -o $@ -c $<
		@printf "\033[33m. \033[39m"
		@echo ""

clean_proj:
		@/bin/rm -f $(OBJ)

clean:
		@make -C libft/ fclean
		@/bin/rm -rf $(OBJDIR)

fclean: clean
		@/bin/rm -f $(NAME)
		@echo "\033[31mRemove\033[39m $(NAME)"

re: fclean all

.PHONY: clean fclean clean_proj compile_lib compile_p norm all