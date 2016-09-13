/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_read3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 16:53:26 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/08 15:24:57 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int     since_last(int k)
{
	int i;
	int a;

	i = 0;
	a = k;
	while (g_shell.shell_line[a] != '\n')
	{
		if (a == 0)
			return (g_cursor.position_line - g_shell.last_backslash + 3);
		a--;
		i++;
	}
	if (i == 0)
	{
		a--;
		while (g_shell.shell_line[a] != '\n')
		{
			if (a == 0)
				return (g_cursor.position_line - g_shell.last_backslash + 3);
			a--;
			i++;
		}
		i++;
	}
	ft_putnbr_fd(i, 2);
	ft_putstr_fd("OIO\n", 2);
	return (i);
}

int		ft_strchr_i(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != c)
	{
		i++;
	}
	return (i);
}


void	go_right(void)
{
	if (g_cursor.position_x_rel == g_shell.shell_win_size - 1 || g_shell.shell_line[g_cursor.position_line] == '\n')
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
	if (g_shell.shell_win_size == 0)
		return (-1);
	if (g_shell.shell_backslash_level > 0)
		return ((g_shell.backslash_index + 3) / g_shell.shell_win_size);
	return ((g_cursor.position_line + 6) / g_shell.shell_win_size);
}

int		get_pos_l(void)
{
	if (g_shell.shell_win_size == 0)
		return (-1);
	if (g_shell.shell_backslash_level > 0)
		return ((g_shell.backslash_index + 2) % g_shell.shell_win_size);
	if ((g_cursor.position_line + 6) % g_shell.shell_win_size == 0)
		return (0);
	else
		return (6 + (g_cursor.position_line % g_shell.shell_win_size));
}

int	get_pos_jump2(void)
{
	int a;
	int i;

	i = 0;
	a = 0;
	while (i < g_cursor.position_line)
	{
		if (g_shell.shell_line[i] == '\n')
		a++;
		i++;
	}
	return (a +((g_cursor.position_line + 6) / g_shell.shell_win_size));
}

int		get_pos_back2(void)
{
	int a;
	int i;
	i = 0;
	a = 0;

	while (i < g_cursor.position_line)
	{
		if (g_shell.shell_line[i] == '\n')
		a++;
		i++;
	}
	return (a +((g_cursor.position_line + 2) / g_shell.shell_win_size));
}

int		get_n_line2(void)
{
	if (g_shell.shell_win_size == 0)
		return (-1);
	if (g_shell.backslash_index == -1)
	{
		return (get_pos_jump2());
	}
	if (g_shell.shell_backslash_level > 0)
		return (get_pos_back2());
	return ((g_cursor.position_line + 6) / g_shell.shell_win_size);
}


int	get_pos_jump(void)
{
	if (ft_strchr_i(g_shell.shell_line, '\n') >= g_cursor.position_line)
	{
		if ((g_cursor.position_line + 6) % g_shell.shell_win_size == 0)
			return (0);
		else
			return (((g_cursor.position_line + 6) % g_shell.shell_win_size));
	}
	else
	{
		return ((since_last(g_cursor.position_line) - 1) % g_shell.shell_win_size);
	}
}

int		get_pos_back(void)
{
	ft_putstr_fd("HERE\n", 2);
	if (g_shell.backslash_index == -1)
	{
		if (ft_strchr_i(g_shell.shell_line, '\n') >= g_cursor.position_line)
		{
			if ((g_cursor.position_line + 2) % g_shell.shell_win_size == 0)
				return (0);
			else
				return (((g_cursor.position_line + 2 - g_shell.last_backslash) % g_shell.shell_win_size));
		}
		else
			return ((since_last(g_cursor.position_line) - 1) % g_shell.shell_win_size);
	}
	else
	{
		ft_putstr_fd("YEP IT, HERE\ns", 2);
			return ((since_last(g_cursor.position_line) - 1) % g_shell.shell_win_size);
		}
}

int		get_pos_l2(void)
{
	if (g_shell.shell_win_size == 0)
		return (-1);
	if (g_shell.backslash_index == -1)
		return (get_pos_jump());
	else if (g_shell.shell_backslash_level > 0)
			return (get_pos_back());
	if ((g_cursor.position_line + 6) % g_shell.shell_win_size == 0)
		return (0);
	else
		return (((g_cursor.position_line + 6) % g_shell.shell_win_size));
}

void  	go_left_jump()
{
	g_cursor.position_line--;
	tputs(tgoto(tgetstr("ch", NULL), 0, \
	get_pos_l2()), 1, tputs_putchar);
	g_cursor.position_line++;
}

void	go_left(void)
{
	ft_putstr_fd("000", 2);
	if (g_cursor.position_x_rel == 0)
	{
		ft_putstr_fd("1111111\n\n", 2);
		tputs(tgetstr("up", NULL), 0, tputs_putchar);
		if (ft_strchr(g_shell.shell_line, '\n'))
			go_left_jump();
		else if (g_shell.selected_end != -2)
		{
			ft_putstr_fd("222222\n\n", 2);
			tputs(tgoto(tgetstr("ch", NULL), 0, \
			g_shell.shell_win_size - 1), 1, tputs_putchar);
		}
	}
	else if (g_cursor.position_line != 0)
	{
		ft_putstr_fd("3333333333\n\n", 2);
		tputs(tgetstr("le", NULL), 0, tputs_putchar);
	}
}


void	update_cursor(void)
{
	if (ft_strchr(g_shell.shell_line, '\n'))
	{
		ft_putstr_fd("NOOOOOOOOO\n\n", 2);
		g_cursor.position_x_rel = get_pos_l2();
		g_cursor.position_y_rel = get_n_line2();
	}
	else
	{
		g_cursor.position_x_rel = get_pos_l();
		g_cursor.position_y_rel = get_n_line();
	}
}
