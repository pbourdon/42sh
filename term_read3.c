/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_read3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 16:53:26 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/28 11:06:52 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int			since_last(int k)
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
	return (i);
}

int			ft_strchr_i(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != c)
	{
		i++;
	}
	return (i);
}

int			get_n_line(void)
{
	if (g_shell.shell_win_size == 0)
		return (-1);
	if (g_shell.shell_backslash_level > 0)
		return ((g_shell.backslash_index + 3) / g_shell.shell_win_size);
	return ((g_cursor.position_line + 6) / g_shell.shell_win_size);
}

int			get_pos_l(void)
{
	if (g_shell.shell_win_size == 0)
		return (-1);
	if (g_shell.shell_backslash_level > 0)
		return ((g_shell.backslash_index + 2) % g_shell.shell_win_size);
	if ((g_cursor.position_line + 6) % g_shell.shell_win_size == 0)
		return (0);
	else
		return (((g_cursor.position_line + 6) % g_shell.shell_win_size));
}
