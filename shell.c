/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 18:02:53 by pguzman           #+#    #+#             */
/*   Updated: 2016/10/17 15:42:59 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int					is_ctrl_c(char *buffer)
{
	if (buffer[0] == 0 && buffer[1] == 0)
	{
		ft_putstr("\n");
		ft_bzero(g_shell.shell_line, g_shell.size);
		return (1);
	}
	return (0);
}

int					sub_listen(char *buffer)
{
	if (is_enter_key(buffer))
	{
		if (press_enter_key())
			return (1);
	}
	else if (is_home_key(buffer))
		press_home_key();
	else if (is_end_key(buffer))
		press_end_key();
	else if (is_option_key(buffer))
		press_option_key(buffer);
	else if (is_shift_direction_key(buffer))
		press_shift_direction_key(buffer);
	else if (is_eot(buffer))
		press_delete_key();
	else if (is_printable_char(buffer))
		press_printable_char(buffer);
	delete_selection_if_other_than_option(buffer);
	return (0);
}

int					listen(char *buffer)
{
	if (is_backspace_key(buffer))
		press_backspace_key();
	else if (is_ctrl_c(buffer))
		return (1);
	else if (is_ctrl_d(buffer) && g_shell.length_line == 0)
	{
		if (g_shell.shell_heredoc == 1)
		{
			ft_putendl("");
			g_shell.shell_heredoc = -1;
			return (1);
		}
		else
		{
			ft_reset_term();
			ft_putendl("exit");
			exit(0);
		}
	}
	else if (is_delete_key(buffer))
		press_delete_key();
	else if (is_direction_key(buffer))
		press_direction_key(buffer);
	return (sub_listen(buffer));
}

void				shell_init(void)
{
	struct winsize	w;

	g_shell.shell_status = 1;
	g_shell.size = 1000;
	g_shell.shell_line = ft_strnew(999);
	g_shell.shell_line_original = (char *)malloc(sizeof(char) * 1000);
	ft_bzero(g_shell.shell_line_original, 1000);
	g_shell.history_index = -1;
	g_shell.backslash_index = -1;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	g_shell.shell_win_size = w.ws_col;
	g_shell.shell_backslash_level = 0;
	g_shell.history = (t_history *)malloc(sizeof(t_history));
	g_shell.history->next = NULL;
	g_shell.history->prev = NULL;
	g_shell.history->str = NULL;
	g_shell.selected_end = -1;
	g_shell.selected_start = -1;
	g_shell.selected_copy = "";
	g_shell.shell_fd_0 = 0;
}

t_history			*double_left(char *fin)
{
	t_history		*hered;

	hered = (t_history *)malloc(sizeof(t_history));
	hered->next = NULL;
	hered->str = NULL;
	g_shell.history_index = get_history_length() + 1;
	g_shell.shell_heredoc = 0;
	while (ft_strcmp(fin, g_shell.shell_line_original) != 0 \
			&& g_shell.shell_heredoc != -1)
	{
		ft_putstr("hdoc> ");
		if (g_shell.shell_heredoc == 0)
			g_shell.shell_heredoc = 1;
		ft_bzero(g_shell.shell_line, g_shell.size);
		shterm_listen(NULL);
		add_to_history(hered, g_shell.shell_line);
	}
	g_shell.shell_heredoc = 0;
	return (hered);
}
