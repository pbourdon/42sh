/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_read5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 10:50:14 by pguzman           #+#    #+#             */
/*   Updated: 2016/09/28 11:01:59 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int					get_pos_jump(void)
{
	if (ft_strchr_i(g_shell.shell_line, '\n') >= g_cursor.position_line)
	{
		if ((g_cursor.position_line + 6) % g_shell.shell_win_size == 0)
			return (0);
		else
			return (((g_cursor.position_line + 6) % g_shell.shell_win_size));
	}
	else
		return (aux1());
}

int					get_pos_back(void)
{
	if (g_shell.backslash_index == -1)
	{
		if (ft_strchr_i(g_shell.shell_line, '\n') >= g_cursor.position_line)
		{
			if ((g_cursor.position_line + 2) % g_shell.shell_win_size == 0)
				return (0);
			else
				return (((g_cursor.position_line + 2 - g_shell.last_backslash) \
							% g_shell.shell_win_size));
		}
		else
			return ((since_last(g_cursor.position_line) - 1) \
					% g_shell.shell_win_size);
	}
	else
		return ((since_last(g_cursor.position_line) - 1) \
				% g_shell.shell_win_size);
}

int					jump_after_last(int a)
{
	int i;

	i = a;
	while (i < g_shell.length_line)
	{
		if (g_shell.shell_line[i] == '\n')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int					jump_after_last_and_here(int a)
{
	int i;

	i = g_shell.last_backslash;
	while (i != a)
	{
		if (g_shell.shell_line[i] == '\n')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int					get_pos_backv2(void)
{
	if (jump_after_last(g_shell.last_backslash))
	{
		if (!jump_after_last_and_here(g_cursor.position_line))
		{
			if ((g_cursor.position_line - g_shell.last_backslash + 2) % \
					g_shell.shell_win_size == 0)
				return (0);
			else
				return (((g_cursor.position_line - g_shell.last_backslash + 2) \
							% g_shell.shell_win_size));
		}
		else
		{
			return (aux1());
		}
	}
	else
	{
		return ((2 + g_shell.backslash_index) % g_shell.shell_win_size);
	}
}
