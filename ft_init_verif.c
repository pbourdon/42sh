/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_verif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 23:20:46 by cmichaud          #+#    #+#             */
/*   Updated: 2016/08/28 23:32:29 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

int				ft_init_verif(void)
{
	char	tabb[3];
	int		n;

	n = 0;
	tabb[0] = 0;
	tabb[1] = 0;
	tabb[2] = 0;
	if ((n = ft_cheat(g_shell.shell_line, tabb, -1)))
	{
		if (n == 1)
			g_shell.shell_line[g_shell.length_line - 1] = ' ';
		g_shell.backslash_index = 0;
		g_shell.shell_backslash_level++;
		g_shell.last_backslash = g_shell.length_line;
		ft_putstr("\n? ");
		return (1);
	}
	return (0);
}
