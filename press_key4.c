/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 14:35:48 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/13 16:58:02 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			press_printable_char(char *buffer)
{
	if (buffer[0] != 0 && !is_enter_key(buffer))
	{
		g_shell.shell_line = add_to_array(g_shell.shell_line, buffer[0], \
				g_cursor.position_line, g_shell.length_line);
		g_shell.length_line++;
		if (ft_strchr(g_shell.shell_line, '\n'))
			movements_delete2(1);
		else
			movements_delete(1);
		if (g_shell.backslash_index >= 0)
			g_shell.backslash_index++;
	}
}

char			quote_oo(int inib, char quote, char c)
{
	if (quote && c == quote)
		quote = 0;
	else if (!inib && !quote && (c == '\'' || c == '"' || c == '`'))
		quote = c;
	return (quote);
}

char			is_a_parenthese(char par, char c)
{
	if (!par && (c == '[' || c == '(' || c == '{'))
		par = c;
	else if (par && ((par == '[' && c == ']') ||
					(par == '{' && c == '}') ||
					(par == '(' && c == ')')))
		par = 0;
	return (par);
}

int				ft_cheat(char *str, char tabb[3], int i)
{
	while (str && str[++i])
	{
		if (!tabb[1] && !tabb[0] && str[i] == '\\')
			tabb[0] = 1;
		else
		{
			tabb[1] = quote_oo(tabb[0], tabb[1], str[i]);
			if (!(tabb[0] + tabb[1]))
				tabb[2] = is_a_parenthese(tabb[2], str[i]);
			tabb[0] = 0;
		}
	}
	i = -1;
	while (++i < 3)
		if (tabb[i])
			return (i + 1);
	return (0);
}

int				ft_init_verif(int n, char *a)
{
	char	tabb[3];

	tabb[0] = 0;
	tabb[1] = 0;
	tabb[2] = 0;
	if ((n = ft_cheat(g_shell.shell_line, tabb, -1)))
	{
		if (n == 1)
			g_shell.shell_line[g_shell.length_line - 1] = ' ';
		if (n == 2)
		{
			g_shell.shell_line = add_to_array(g_shell.shell_line, a[0], \
					g_cursor.position_line, g_shell.length_line);
			g_shell.length_line++;
			(ft_strchr(g_shell.shell_line, '\n')) ? movements_delete2(1) : \
				movements_delete(1);
			(g_shell.backslash_index >= 0) ? g_shell.backslash_index++ : 0;
		}
		g_shell.backslash_index = 0;
		g_shell.shell_backslash_level++;
		g_shell.last_backslash = g_shell.length_line;
		ft_putstr((n == 1 || n == 3) ? "\n? " : "? ");
		return (1);
	}
	return (0);
}
