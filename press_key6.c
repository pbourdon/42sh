/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 14:36:34 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/13 16:58:54 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			press_shift_up2(void)
{
	int			h;
	int			k;

	k = g_cursor.position_x_rel;
	h = g_cursor.position_line;
	while (h > 0)
	{
		if (g_shell.backslash_index == 0)
			break ;
		go_left(g_cursor, g_shell);
		move_cursor_left(g_cursor, g_shell);
		update_cursor();
		if (g_cursor.position_x_rel == k)
			break ;
		if (g_shell.backslash_index > 0)
			g_shell.backslash_index--;
		h--;
	}
}

void			press_shift_up(void)
{
	int			h;
	int			k;

	if (ft_strchr(g_shell.shell_line, '\n'))
	{
		press_shift_up2();
		return ;
	}
	k = g_shell.shell_win_size;
	h = g_cursor.position_line;
	while (h > 0 && k > 0)
	{
		if (g_shell.backslash_index == 0)
			break ;
		go_left(g_cursor, g_shell);
		move_cursor_left(g_cursor, g_shell);
		if (g_shell.backslash_index > 0)
			g_shell.backslash_index--;
		h--;
		k--;
	}
}

void			press_shift_down2(void)
{
	int			h;
	int			k;

	k = g_cursor.position_x_rel;
	h = g_cursor.position_line;
	while (h < g_shell.length_line)
	{
		if (g_shell.backslash_index != -1)
			g_shell.backslash_index++;
		go_right(g_cursor, g_shell);
		move_cursor_right(g_cursor, g_shell);
		if (ft_strchr(g_shell.shell_line, '\n'))
			update_cursor();
		if (g_cursor.position_x_rel == k)
			break ;
		h++;
	}
}

void			press_shift_down(void)
{
	int			h;
	int			k;

	if (ft_strchr(g_shell.shell_line, '\n'))
	{
		press_shift_down2();
		return ;
	}
	k = g_shell.shell_win_size;
	h = g_cursor.position_line;
	while (h < g_shell.length_line && k > 0)
	{
		if (g_shell.backslash_index != -1)
			g_shell.backslash_index++;
		go_right(g_cursor, g_shell);
		move_cursor_right(g_cursor, g_shell);
		h++;
		k--;
	}
}

char			*extract_str(char *str, int a, int b)
{
	char		*res;
	int			i;
	int			temp;

	i = 0;
	temp = b - a + 1;
	res = (char *)malloc(sizeof(*res) * (b - a + 2));
	res[b - a + 1] = '\0';
	while (i < (temp))
	{
		res[i] = str[a];
		a++;
		i++;
	}
	return (res);
}
