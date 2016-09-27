/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 14:35:27 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/27 17:51:58 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			press_down_key(void)
{
	t_history	*history;

	history = g_shell.history;
	if (g_shell.history_index < get_history_length(history))
	{
		if (g_shell.backslash_index != -1)
			replace_shell_backslash_line(get_history_i(g_shell.history_index));
		else
			replace_shell_line(get_history_i(g_shell.history_index));
		g_shell.history_index++;
	}
	else if (g_shell.history_index == get_history_length(history))
	{
		g_shell.history_index = get_history_length(history) + 1;
		if (g_shell.backslash_index == -1)
			replace_shell_line(g_shell.shell_line_original);
		else
			replace_shell_backslash_line(g_shell.shell_line_original);
	}
}

void			press_left_key(void)
{
	if (g_cursor.position_line > 0 && g_shell.backslash_index != 0)
	{
		go_left(g_cursor, g_shell);
		move_cursor_left(g_cursor, g_shell);
	}
	if (g_shell.backslash_index > 0)
		g_shell.backslash_index--;
}

void			press_right_key(void)
{
	if (g_cursor.position_line < g_shell.length_line)
	{
		if (g_shell.backslash_index != -1)
			g_shell.backslash_index++;
		go_right(g_cursor, g_shell);
		move_cursor_right(g_cursor, g_shell);
	}
}

void			press_home_key(void)
{
	int			h;

	h = g_cursor.position_line;
	while (h > 0)
	{
		if (g_shell.backslash_index == 0)
			break ;
		press_left_key();
		h--;
		if (ft_strchr(g_shell.shell_line, '\n'))
			update_cursor();
	}
}

void			press_end_key(void)
{
	int			h;

	h = g_cursor.position_line;
	while (h < g_shell.length_line)
	{
		if (g_shell.backslash_index != -1)
			g_shell.backslash_index++;
		go_right(g_cursor, g_shell);
		move_cursor_right(g_cursor, g_shell);
		h++;
		if (ft_strchr(g_shell.shell_line, '\n'))
			update_cursor();
	}
}
