/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 10:39:08 by pguzman           #+#    #+#             */
/*   Updated: 2016/09/28 11:02:25 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			press_option_c(void)
{
	if (g_shell.selected_start != -1 && g_shell.selected_end != -1)
	{
		if (ft_strcmp(g_shell.selected_copy, "") != 0)
			ft_strdel(&g_shell.selected_copy);
		g_shell.selected_copy = extract_str(g_shell.shell_line, \
				g_shell.selected_start, g_shell.selected_end);
	}
}

void			press_option_v(void)
{
	char		*str;
	size_t		i;
	char		a[2];

	i = 0;
	str = g_shell.selected_copy;
	a[1] = '\0';
	while (i < ft_strlen(str))
	{
		a[0] = str[i];
		press_printable_char(a);
		i++;
	}
}

void			press_up_key(void)
{
	t_history	*history;

	if (g_shell.history_index > 0)
	{
		history = g_shell.history;
		if (g_shell.backslash_index != -1)
		{
			g_shell.history_index--;
			if (g_shell.history_index > 0)
				replace_shell_backslash_line(
				get_history_i(g_shell.history_index - 1));
			if (g_shell.history_index == 0)
				g_shell.history_index++;
		}
		else if (g_shell.history_index != 1)
		{
			g_shell.history_index--;
			replace_shell_line(get_history_i(g_shell.history_index - 1));
		}
	}
}

void			print_history(t_history *history)
{
	t_history	*his;

	his = history;
	while (his)
	{
		ft_putstr_fd(his->str, 2);
		ft_putstr_fd("\n", 2);
		his = his->next;
	}
}
