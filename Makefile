# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/02 13:52:37 by bde-maze          #+#    #+#              #
#    Updated: 2016/08/22 18:16:50 by cmichaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

HEADER = includes/minishell.h

FLAGS = -Wall -Werror -Wextra -g3 -O3

SRC = 	builtin_exit_error.c \
		space_treatment.c \
		term_functions.c \
		split_on_spec.c \
		old_functions.c \
		parseandexc2.c \
		new_arg_to_list.c \
		parseandexc.c \
		press_key1.c \
		add_letter.c \
		good_order.c \
		allwrites.c \
		term_read.c \
		unsetenv.c \
		go_words.c \
		is_key1.c \
		to_tree.c \
		history.c \
		setenv2.c \
		spliter.c \
		tools2.c \
		setenv.c \
		signal.c \
		cursor.c \
		tools.c \
		error.c \
		shell.c \
		env2.c \
		env3.c \
		main.c \
		main2.c \
		free.c \
		env.c \
		prompt.c \
		cd2.c \
		cd3.c \
		cd.c \
		agreg.c \
		ft_redirect4.c \
		testredi.c \
		testredi2.c \
		testredi3.c \
		testredi4.c \
		testredi5.c \
		testredi6.c \
		tools_split.c \

OBJDIR = obj/

OBJ = $(SRC:%.c=$(OBJDIR)%.o)

all: $(NAME)

norm:
	@norminette $(SRC) $(HEADER)

$(NAME): compile_lib compile_p $(OBJ)
		@clang $(FLAGS) -lncurses -o $(NAME) $(OBJ) -L libft -lft
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
