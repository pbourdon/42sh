/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 14:35:48 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/28 20:53:02 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void			press_printable_char(char *buffer)
{
	if (buffer[0] != 0 && !is_enter_key(buffer))
	{
		g_shell.shell_line = add_to_array(g_shell.shell_line, buffer[0], \
				g_cursor.position_line, g_shell.length_line);
		g_shell.length_line++;
		movements_delete(1);
		if (g_shell.backslash_index >= 0)
			g_shell.backslash_index++;
	}
}

int				ft_strchr_i(char *s, char c)
{
	int			i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int				check_char(int *q, int a[], char ch)
{
	char		*str;
	int			y;

	str = "a({[]})`\"'";
	y = ft_strchr_i(str, ch);
	if (y)
	{
		if (y == 1)
			(a[0])++;
		else if (y == 2)
			(a[1])++;
		else if (y == 3)
			(a[2])++;
		else if (y == 4)
			(a[2])--;
		else if (y == 5)
			(a[1])--;
		else if (y == 6)
			(a[0])--;
		else if (y > 6 && y < 10)
			(*q)++;
		return (a[0] < 0 || a[1] < 0 || a[2] < 0) ? 0 : 1;
	}
	return (1);
}

char			quote_oo(int inib, char quote, char c)
{
	if (quote && c == quote)
		quote = 0;
	else if (!inib && !quote && (c == '\'' || c == '"' || c == '`'))
		quote = c;
	return (quote);
}

char            is_a_parenthese(char par, char c)
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

int 			ft_init_verif(void)
{
	char tabb[3];
	int n;

	n = 0;
	tabb[0] = 0 ;
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

int				check_par_and_quotes(int *q, int a[])
{
	int			i;
	int			j;

	i = 0;
	while (i < g_shell.length_line)
	{
		j = 0;
		if (!check_char(q, a, g_shell.shell_line[i]))
			return (0);
		i++;
	}
	return (1);
}

int				parenthesis_closed(void)
{
	int			quotes_paired;
	int			par_paired[3];

	quotes_paired = 0;
	par_paired[0] = 0;
	par_paired[1] = 0;
	par_paired[2] = 0;
	if (!check_par_and_quotes(&quotes_paired, par_paired))
	{
		ft_putstr("\nSyntax error");
		return (2);
	}
	if ((quotes_paired % 2 == 0) && par_paired[0] == 0 && par_paired[1] == 0 \
			&& par_paired[2] == 0)
		return (1);
	else
	{
		g_shell.backslash_index = 0;
		g_shell.shell_backslash_level++;
		g_shell.last_backslash = g_shell.length_line;
		ft_putstr("\n? ");
		return (0);
	}
}
