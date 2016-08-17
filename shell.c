/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <pguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 09:43:51 by pguzman           #+#    #+#             */
/*   Updated: 2016/08/05 16:31:09 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		shell_loop(t_term *term, t_data *data)
{
	while (shell.shell_status)
	{
		shell.shell_backslash_level = 0;
		shell.last_backslash = 0;
		shell.history_index = get_history_length() + 1;
		prompt_line();
		// ft_putchar('>');
		if (!shterm_listen(term))
		{
			ft_putstr("exit\nexit\n");
			return (0);
		}
		readgnl(data, shell.shell_line);
		if ((shell.shell_line)[0] == '\0')
			continue ;
	}
	return (0);
}

int		shterm_listen(t_term *term)
{
	term->term_name = "a";
	cursor_init();
	shell.length_line = 0;
	ft_bzero(shell.shell_line, 1000);
	shell_listening_char();
	return (-1);
}

void	update_shell_line_original(void)
{
	if (shell.history_index == get_history_length() + 1)
	{
		if (shell.backslash_index == -1)
		{
			if (ft_strcmp(shell.shell_line, shell.shell_line_original) != 0)
			{
				ft_strdel(&shell.shell_line_original);
				shell.shell_line_original = ft_strdup(shell.shell_line);
			}
		}
		else if (shell.shell_backslash_level != 0)
		{
			ft_strdel(&shell.shell_line_original);
			shell.shell_line_original = ft_strdup(\
					&shell.shell_line[shell.last_backslash]);
		}
	}
}

void	shell_listening_char(void)
{
	struct winsize	w;
	char			*buffer;


	while (1)
	{
		buffer = (char *)malloc(sizeof(*buffer) * 9);
		buffer[8] = '\0';
		update_shell_line_original();
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		shell.shell_win_size = w.ws_col;
		update_cursor();
		prepare_to_listen(buffer);
		if (listen(buffer))
			break ;
		ft_strdel(&buffer);
	}
	ft_strdel(&buffer);
}

void	prepare_to_listen(char buffer[9])
{
	int				ret;

	ft_bzero(buffer, 9);
	signal(SIGWINCH, sig_handler);
	ret = read(0, buffer, 8);
	buffer[ret] = '\0';
	// print_buffer(buffer);
}

void	delete_selection_if_other_than_option(char *buffer)
{
	int	temp;

	if (!is_option_left(buffer) && !is_option_right(buffer))
	{
		if (shell.selected_end != -1 && shell.selected_start != -1)
		{
			shell.selected_end = -1;
			shell.selected_start = -1;
			temp = cursor.position_line;
			press_home_key();
			press_printable_char(" ");
			press_backspace_key();
			while (cursor.position_line < temp)
				press_right_key();
		}
	}
}

int		listen(char *buffer)
{
	if (is_backspace_key(buffer))
		press_backspace_key();
	else if (is_delete_key(buffer))
		press_delete_key();
	else if (is_direction_key(buffer))
		press_direction_key(buffer);
	else if (is_home_key(buffer))
		press_home_key();
	else if (is_end_key(buffer))
		press_end_key();
	else if (is_option_key(buffer))
		press_option_key(buffer);
	else if (is_enter_key(buffer))
	{
		if (press_enter_key())
			return (1);
	}
	else if (is_shift_direction_key(buffer))
		press_shift_direction_key(buffer);
	else if (is_eot(buffer))
		press_delete_key();
	else if (is_printable_char(buffer))
		press_printable_char(buffer);
	delete_selection_if_other_than_option(buffer);
	return (0);
}

void	shell_init(void)
{
	struct winsize w;

	shell.shell_status = 1;
	shell.shell_line = (char *)malloc(sizeof(*(shell.shell_line)) * 1000);
	shell.shell_line[999] = '\0';

	shell.shell_line_original = (char *)malloc(sizeof(char) * 1000);
	ft_bzero(shell.shell_line_original, 1000);
	shell.history_index = -1;
	shell.backslash_index = -1;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	shell.shell_win_size = w.ws_col;
	shell.shell_backslash_level = 0;
	shell.history = malloc(sizeof(*(shell.history)));
	shell.history->next = NULL;
	shell.history->str = NULL;
	shell.selected_end = 0;
	shell.selected_start = 0;
	shell.selected_copy = "";
}
