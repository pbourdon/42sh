/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 14:35:10 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/28 10:37:29 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			movements_delete(int a)
{
	int h[2];

	tputs(tgetstr("cd", NULL), 0, tputs_putchar);
	h[0] = ft_putstr_i(g_shell.shell_line, g_cursor.position_line);
	h[1] = h[0];
	while (h[0] - 1 > 0)
	{
		move_cursor_right(g_cursor, g_shell);
		h[0]--;
	}
	if ((g_cursor.position_x_rel == g_shell.shell_win_size - 1) && \
			g_cursor.position_line != g_shell.length_line)
	{
		ft_putstr(" ");
		tputs(tgetstr("le", NULL), 0, tputs_putchar);
	}
	move_cursor_right(g_cursor, g_shell);
	while (h[1] - a > 0)
	{
		go_left(g_cursor, g_shell);
		move_cursor_left(g_cursor, g_shell);
		h[1]--;
	}
}

void			movements_delete2(int a)
{
	int h[2];

	tputs(tgetstr("cd", NULL), 0, tputs_putchar);
	h[0] = ft_putstr_i(g_shell.shell_line, g_cursor.position_line);
	h[1] = h[0];
	while (h[0] - 1 > 0)
	{
		move_cursor_right(g_cursor, g_shell);
		h[0]--;
	}
	if (g_cursor.position_x_rel == g_shell.shell_win_size - 1)
	{
		ft_putstr(" ");
		tputs(tgetstr("le", NULL), 0, tputs_putchar);
	}
	move_cursor_right(g_cursor, g_shell);
	update_cursor();
	while (h[1] - a > 0)
	{
		go_left(g_cursor, g_shell);
		move_cursor_left(g_cursor, g_shell);
		update_cursor();
		h[1]--;
	}
}

void			press_backspace_key2(void)
{
	int		temp;

	if (g_cursor.position_line > 0 && g_shell.backslash_index != 0)
	{
		g_shell.shell_line =
			del_from_arr(g_shell.shell_line, g_cursor.position_line);
		g_shell.length_line--;
		temp = g_shell.selected_end;
		g_shell.selected_end = -2;
		press_left_key();
		g_shell.selected_end = temp;
		movements_delete2(0);
	}
}

void			press_backspace_key(void)
{
	if (ft_strchr(g_shell.shell_line, '\n'))
	{
		press_backspace_key2();
		return ;
	}
	if (g_cursor.position_line > 0 && g_shell.backslash_index != 0)
	{
		g_shell.shell_line =
			del_from_arr(g_shell.shell_line, g_cursor.position_line);
		g_shell.length_line--;
		press_left_key();
		movements_delete(0);
	}
}

void			press_delete_key(void)
{
	if (g_cursor.position_line >= 0 &&
		g_cursor.position_line != g_shell.length_line)
	{
		g_shell.shell_line = del_from_arr(g_shell.shell_line, \
				g_cursor.position_line + 1);
		g_shell.length_line--;
		if (ft_strchr(g_shell.shell_line, '\n'))
			movements_delete2(0);
		else
			movements_delete(0);
	}
}
