/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <pguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 10:23:53 by pguzman           #+#    #+#             */
/*   Updated: 2016/08/05 11:13:22 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		ft_putstr_i(char *str, int i)
{
	int res;

	res = 0;
	while (str[i])
	{
		if (i >= shell.selected_start && i <= shell.selected_end)
		{
			tputs(tgetstr("mr", NULL), 0, tputs_putchar);
		}
		ft_putchar(str[i]);
		i++;
		res++;
		tputs(tgetstr("me", NULL), 0, tputs_putchar);
	}
	return (res);
}

char	*add_to_array(char *str, char c, int i, int len)
{
	while (len >= i)
	{
		str[len + 1] = str[len];
		len--;
	}
	str[i] = c;
	return (str);
}

char	*del_from_arr(char *str, int i)
{
	while (str[i])
	{
		str[i - 1] = str[i];
		i++;
	}
	str[i - 1] = '\0';
	return (str);
}

void	move_cursor_left(void)
{
	if (cursor.position_line != 0)
	{
		cursor.position_line--;
		if (cursor.position_x_rel == 0)
		{
			cursor.position_y_rel--;
			cursor.position_x_rel = shell.shell_win_size - 1;
			cursor.position_y_abs--;
		}
		else
			cursor.position_x_rel--;
	}
}

void	move_cursor_right(void)
{
	if (cursor.position_line < shell.length_line)
	{
		if (cursor.position_x_rel == shell.shell_win_size - 1)
		{
			cursor.position_x_rel = -1;
			cursor.position_y_abs++;
		}
		cursor.position_line++;
		cursor.position_x_rel++;
	}
}

void	go_left(void)
{
	if (cursor.position_x_rel == 0)
	{
		tputs(tgetstr("up", NULL), 0, tputs_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, \
					shell.shell_win_size - 1), 1, tputs_putchar);
	}
	else if (cursor.position_line != 0)
	{
		tputs(tgetstr("le", NULL), 0, tputs_putchar);
	}
}

void	go_right(void)
{
	if (cursor.position_x_rel == shell.shell_win_size - 1)
	{
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, tputs_putchar);
		tputs(tgetstr("do", NULL), 0, tputs_putchar);
	}
	else
	{
		tputs(tgoto(tgetstr("nd", NULL), 0, 0), 0, tputs_putchar);
	}
}

int		get_n_line(void)
{
	if (shell.shell_win_size == 0)
		return (-1);
	if (shell.shell_backslash_level > 0)
		return ((shell.backslash_index + 3) / shell.shell_win_size);
	return ((cursor.position_line + 1) / shell.shell_win_size);
}

int		get_pos_l(void)
{
	if (shell.shell_win_size == 0)
		return (-1);
	if (shell.shell_backslash_level > 0)
		return ((shell.backslash_index + 2) % shell.shell_win_size);
	if ((cursor.position_line + 1) % shell.shell_win_size == 0)
		return (0);
	else
		return (1 + (cursor.position_line % shell.shell_win_size));
}

void	update_cursor(void)
{
	// ft_putstr_fd("update_cursor\n", 2);
	cursor.position_x_rel = get_pos_l();
	cursor.position_y_rel = get_n_line();
}

void	delete_shell_line(void)
{
	press_home_key();
	tputs(tgetstr("cd", NULL), 0, tputs_putchar);
}

void	replace_shell_line(char *str)
{
	delete_shell_line();
	ft_bzero(shell.shell_line, 1000);
	shell.shell_line = ft_strcat(shell.shell_line, str);
	shell.length_line = ft_strlen(str);
	cursor.position_line = shell.length_line;
	ft_putstr(shell.shell_line);
	if (shell.length_line == shell.shell_win_size - 1)
	{
		ft_putstr(" ");
		tputs(tgetstr("le", NULL), 0, tputs_putchar);
	}
	update_cursor();
}

void	delete_shell_backslash_line(void)
{
	int i;

	i = 0;
	while (shell.backslash_index != 0)
	{
		press_left_key();
		shell.shell_line[shell.last_backslash + i] = '\0';
		shell.length_line--;
		i++;
	}
	tputs(tgetstr("cd", NULL), 0, tputs_putchar);
}

void	replace_shell_backslash_line(char *str)
{
	int		i;
	char	*del;

	i = shell.last_backslash;
	delete_shell_backslash_line();
	ft_putstr(str);
	i = ft_strlen(str);
	while (i > 0)
	{
		shell.backslash_index++;
		shell.length_line++;
		cursor.position_line++;
		i--;
	}
	del = shell.shell_line;
	shell.shell_line = ft_strcat(shell.shell_line, str);
}
