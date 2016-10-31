/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_read6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 10:50:02 by pguzman           #+#    #+#             */
/*   Updated: 2016/09/28 11:02:18 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int			get_pos_jump2(void)
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
	return (a + ((g_cursor.position_line + 6) / g_shell.shell_win_size));
}

int			get_pos_back2(void)
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
	return (a + ((g_cursor.position_line + 2) / g_shell.shell_win_size));
}

int			get_n_line2(void)
{
	if (g_shell.shell_win_size == 0)
		return (-1);
	if (g_shell.backslash_index == -1)
		return (get_pos_jump2());
	if (g_shell.shell_backslash_level > 0)
		return (get_pos_back2());
	return ((g_cursor.position_line + 6) / g_shell.shell_win_size);
}

int			aux1(void)
{
	int i;
	int j;

	i = 0;
	j = g_cursor.position_line;
	while (g_shell.shell_line[j - 1] != '\n')
	{
		if (j == 1)
			break ;
		j--;
		i++;
	}
	return (i % g_shell.shell_win_size);
}

int			aux2(void)
{
	int i;
	int j;

	i = 0;
	j = g_cursor.position_line;
	while (g_shell.shell_line[j - 1] != '\n')
	{
		if (j == 1)
			break ;
		j--;
		i++;
	}
	return ((i + 2) % g_shell.shell_win_size);
}
