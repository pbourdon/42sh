# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/02 13:52:37 by bde-maze          #+#    #+#              #
#    Updated: 2016/10/22 11:33:49 by bde-maze         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

HEADER = includes/shell.h

FLAGS = -Wall -Wextra -Werror -g3 -o3

SRC = 	builtin_exit_error.c \
		designator_string.c \
		history_show_func.c \
		split_inib_tools.c \
		new_arg_to_list.c \
		space_treatment.c \
		term_functions.c \
		history_option.c \
		split_on_spec.c \
		old_functions.c \
		history_tools.c \
		parseandexc2.c \
		ft_redirect4.c \
		tools_split.c \
		parseandexc.c \
		nsplit_inib.c \
		check_error.c \
		press_key1.c \
		press_key2.c \
		press_key3.c \
		press_key4.c \
		press_key5.c \
		press_key6.c \
		press_key7.c \
		add_letter.c \
		good_order.c \
		term_read2.c \
		term_read3.c \
		term_read4.c \
		term_read5.c \
		term_read6.c \
		designator.c \
		env_tools.c \
		shell_lvl.c \
		allwrites.c \
		term_read.c \
		unsetenv.c \
		builenv3.c \
		builenv2.c \
		go_words.c \
		cd_getpwd.c \
		is_key1.c \
		is_key2.c \
		is_key3.c \
		is_key4.c \
		is_key5.c \
		to_tree.c \
		history.c \
		setenv2.c \
		spliter.c \
		builenv.c \
		prompt.c \
		tools2.c \
		setenv.c \
		signal.c \
		cursor.c \
		shell2.c \
		shell3.c \
		error2.c \
		cdcall.c \
		tools.c \
		agreg.c \
		shell.c \
		main2.c \
		hash2.c \
		hash3.c \
		callecho.c \
		env_var_handle.c \
		history_norm_tool.c \
		export_on_pipe.c \
		main_loop.c \
		echo.c \
		env2.c \
		env3.c \
		main.c \
		free.c \
		hash.c \
		env.c \
		cd2.c \
		cd3.c \
		cd.c \
		launch_main_fork.c \
		redi_handler.c \
		redi_heredochandler.c \
		redi_handle_tool.c \
		builtin_handler.c \
		final_liste.c \
		free_all.c \
		free_all_norm.c \
		split_on_spec_norm.c \
		designator_exec.c \
		parsecommand.c \
		search_tild.c \
		search_var.c \
		wait_all_pid.c \
		init_hash.c \
		ft_designator.c \
		ft_replace_designator.c \
		ft_tools_for_designator.c \
		ft_read.c \
		ft_add_data.c \
		ft_ins_avant.c \
		nik_the_norm.c \
		dlist_new.c \
		ft_display_list.c \
		check_comp_norm.c \
		press_tab_key.c \
		replace_word_completion.c \
		completion_p1.c \
		print_completion.c \
		print_completion2.c \
		file_build_completion.c \
		bin_build_completion.c \
		ft_read2.c \
		ft_delete_list.c \
		get_keys_var_value.c

OBJDIR = obj/

OBJ = $(SRC:%.c=$(OBJDIR)%.o)

all: $(NAME)

norm:
	@norminette $(SRC) $(HEADER)

$(NAME): compile_lib compile_p $(OBJ)
		@clang $(FLAGS) -ltermcap -o $(NAME) $(OBJ) -L libft -lft
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
