/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <pguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 09:43:51 by pguzman           #+#    #+#             */
/*   Updated: 2016/08/25 16:07:40 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void 	*realloc(void *ptr, size_t size)
{
	char	*newptr;

	newptr = NULL;
	if (ptr)
	{
		newptr = (char *)malloc(size);
		if (!newptr)
			return (NULL);
		ft_memcpy(newptr, ptr, size);
		ft_memdel(&ptr);
	}
	return (newptr);
}

int					shell_loop(t_term *term, t_data *data, char **env)
{
	while (g_shell.shell_status)
	{
		g_shell.shell_backslash_level = 0;
		g_shell.last_backslash = 0;
		g_shell.history_index = get_history_length() + 1;
		prompt_line(env);
		if (!shterm_listen(term))
		{
			ft_putstr("exit\nexit\n");
			return (0);
		}
		readgnl(data, g_shell.shell_line);
		if ((g_shell.shell_line)[0] == '\0')
			continue ;
	}
	return (0);
}

int					shterm_listen(t_term *term)
{
	if (term)
		term->term_name = "a";
	cursor_init();
	g_shell.length_line = 0;
	ft_bzero(g_shell.shell_line, g_shell.size);
	shell_listening_char();
	return (-1);
}

void				update_shell_line_original(void)
{
	if (g_shell.history_index == get_history_length() + 1)
	{
		if (g_shell.backslash_index == -1)
		{
			if (ft_strcmp(g_shell.shell_line, g_shell.shell_line_original) != 0)
			{
				ft_bzero(g_shell.shell_line_original, g_shell.size);
				g_shell.shell_line_original = ft_strcat(g_shell.shell_line_original, g_shell.shell_line);
			}
		}
		else if (g_shell.shell_backslash_level != 0)
		{
			ft_bzero(g_shell.shell_line_original, g_shell.size);
			g_shell.shell_line_original = ft_strcat(g_shell.shell_line_original, &g_shell.shell_line[g_shell.last_backslash]);
		}
	}
	if (g_shell.length_line > (g_shell.size / 2) - 20)
	{
		g_shell.size = g_shell.size * 2;
		g_shell.shell_line = realloc(g_shell.shell_line, g_shell.size);
	}
}


void		sig_handler3(int sign)
{
	sign = 1;
	g_shell.shell_fd_0 = dup(0);
	close(0);
}

void		sig_handler2(int sign)
{
	sign = 1;
	ft_putendl("");
}

void				shell_listening_char(void)
{
	struct winsize	w;
	char			*buffer;

	while (1)
	{
		signal(SIGINT, sig_handler3);
		signal(SIGQUIT, sig_handler3);
		signal(SIGTSTP, sig_handler3);
		buffer = (char *)malloc(sizeof(*buffer) * 9);
		buffer[8] = '\0';
		update_shell_line_original();
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		g_shell.shell_win_size = w.ws_col;
		update_cursor();
		prepare_to_listen(buffer);
		if (listen(buffer))
			break ;
		ft_strdel(&buffer);
	}
	signal(SIGINT, sig_handler2);
	signal(SIGQUIT, sig_handler2);
	signal(SIGTSTP, sig_handler2);
	ft_strdel(&buffer);
}

void				prepare_to_listen(char buffer[9])
{
	int				ret;

	ft_bzero(buffer, 9);
	signal(SIGWINCH, sig_handler);
	ret = read(0, buffer, 8);
	if (g_shell.shell_fd_0)
	{
		dup2(g_shell.shell_fd_0, 0);
		if (ret == -1)
		{
			buffer[0] = 0;
			buffer[1] = 0;
		}
		g_shell.shell_fd_0 = 0;
	}
	if (ret > -1)
		buffer[ret] = '\0';
}

void				delete_selection_if_other_than_option(char *buffer)
{
	int				temp;

	if (!is_option_left(buffer) && !is_option_right(buffer))
	{
		if (g_shell.selected_end != -1 && g_shell.selected_start != -1)
		{
			g_shell.selected_end = -1;
			g_shell.selected_start = -1;
			temp = g_cursor.position_line;
			press_home_key();
			press_printable_char(" ");
			press_backspace_key();
			while (g_cursor.position_line < temp)
				press_right_key();
		}
	}
}

int		is_ctrl_c(char *buffer)
{
	if (buffer[0] == 0 && buffer[1] == 0)
	{
		ft_putstr("\n");
		ft_bzero(g_shell.shell_line, g_shell.size);
		return (1);
	}
	return (0);
}

int					listen(char *buffer)
{
	if (is_backspace_key(buffer))
		press_backspace_key();
	else if (is_ctrl_c(buffer))
		return (1);
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

void				shell_init(void)
{
	struct winsize	w;

	g_shell.shell_status = 1;
	g_shell.size = 1000;
	g_shell.shell_line = (char *)malloc(sizeof(*(g_shell.shell_line)) * 1000);
	g_shell.shell_line[999] = '\0';
	g_shell.shell_line_original = (char *)malloc(sizeof(char) * 1000);
	ft_bzero(g_shell.shell_line_original, 1000);
	g_shell.history_index = -1;
	g_shell.backslash_index = -1;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	g_shell.shell_win_size = w.ws_col;
	g_shell.shell_backslash_level = 0;
	g_shell.history = malloc(sizeof(*(g_shell.history)));
	g_shell.history->next = NULL;
	g_shell.history->str = NULL;
	g_shell.selected_end = 0;
	g_shell.selected_start = 0;
	g_shell.selected_copy = "";
	g_shell.shell_fd_0 = 0;
}

t_history			*double_left(char *fin)
{
	t_history		*hered;

	hered = malloc(sizeof(*(hered)));
	hered->next = NULL;
	hered->str = NULL;
	g_shell.history_index = get_history_length() + 1;
	while (ft_strcmp(fin, g_shell.shell_line_original) != 0)
	{
		ft_putstr("heredoc>");
		g_shell.shell_heredoc = 1;
		ft_bzero(g_shell.shell_line, g_shell.size);
		shterm_listen(NULL);
		add_to_history(hered, g_shell.shell_line);
	}
	return (hered);
}
