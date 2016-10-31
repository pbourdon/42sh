/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_read4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 10:50:28 by pguzman           #+#    #+#             */
/*   Updated: 2016/09/28 11:06:54 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int			get_pos_l2(void)
{
	if (g_shell.shell_win_size == 0)
		return (-1);
	if (g_shell.backslash_index == -1)
		return (get_pos_jump());
	else if (g_shell.shell_backslash_level > 0)
		return (get_pos_backv2());
	if ((g_cursor.position_line + 6) % g_shell.shell_win_size == 0)
		return (0);
	else
		return (((g_cursor.position_line + 6) % g_shell.shell_win_size));
}

void		go_left_jump(void)
{
	if (g_shell.backslash_index != -1)
	{
		g_shell.backslash_index--;
		g_cursor.position_line--;
		tputs(tgoto(tgetstr("ch", NULL), 0, \
					get_pos_l2()), 1, tputs_putchar);
		g_shell.backslash_index++;
		g_cursor.position_line++;
	}
	else
	{
		g_cursor.position_line--;
		tputs(tgoto(tgetstr("ch", NULL), 0, \
					get_pos_l2()), 1, tputs_putchar);
		g_cursor.position_line++;
	}
}

void		go_left(void)
{
	if (g_cursor.position_x_rel == 0)
	{
		tputs(tgetstr("up", NULL), 0, tputs_putchar);
		if (ft_strchr(g_shell.shell_line, '\n'))
			go_left_jump();
		else if (g_shell.selected_end != -2)
		{
			tputs(tgoto(tgetstr("ch", NULL), 0, \
						g_shell.shell_win_size - 1), 1, tputs_putchar);
		}
	}
	else if (g_cursor.position_line != 0)
	{
		tputs(tgetstr("le", NULL), 0, tputs_putchar);
	}
}

void		update_cursor(void)
{
	if (ft_strchr(g_shell.shell_line, '\n'))
	{
		g_cursor.position_x_rel = get_pos_l2();
		g_cursor.position_y_rel = get_n_line2();
	}
	else
	{
		g_cursor.position_x_rel = get_pos_l();
		g_cursor.position_y_rel = get_n_line();
	}
}

void		go_right(void)
{
	if (g_cursor.position_x_rel == g_shell.shell_win_size - 1 \
			|| g_shell.shell_line[g_cursor.position_line] == '\n')
	{
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, tputs_putchar);
		tputs(tgetstr("do", NULL), 0, tputs_putchar);
	}
	else
	{
		tputs(tgoto(tgetstr("nd", NULL), 0, 0), 0, tputs_putchar);
	}
}
