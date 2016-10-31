/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 10:02:30 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/21 10:45:06 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int			bin_or_file(int q, int i, char c, int len)
{
	if (q + i || (c != '"' && c != '\'' && c != '\\' && c != ' '))
	{
		if (!len)
			len = 1;
	}
	if (!q && !i && (c == '|' || c == '&' || c == ';'))
		return (0);
	if (!q && !i && c == ' ')
	{
		if (len == 1)
			len = 2;
		return (len);
	}
	if (!len)
		len = 1;
	return (len);
}

int			binary_or_file(char *cmd, int x, int inib, int quote)
{
	int i;
	int len;

	i = -1;
	len = 0;
	while (cmd[++i])
	{
		if (!quote && !inib && cmd[i] == '\\')
			inib = 1;
		else
		{
			quote = quote_norm(inib, quote, cmd[i]);
			len = bin_or_file(quote, inib, cmd[i], len);
			inib = 0;
		}
		if (i == x)
			return (len);
	}
	return (len);
}

char		*cpy_inib_path(char *cmd, int len, int quote, int inib)
{
	char	*path;
	int		j;
	int		i;

	j = -1;
	i = -1;
	path = (char *)malloc(sizeof(char) * (len + 1));
	path[len] = 0;
	while (cmd[++i])
		if (!quote && !inib && cmd[i] == '\\')
			inib = 1;
		else if (!(inib + quote) && j != -1 && cmd[i] == ' ')
		{
			path[++j] = 0;
			return (path);
		}
		else
		{
			quote = quote_norm(inib, quote, cmd[i]);
			if (is_a_word(quote, inib, cmd[i]))
				path[++j] = cmd[i];
			inib = 0;
		}
	return (path);
}

char		*get_inib_path(char *cmd, int i, int quote, int inib)
{
	int len;
	int x;

	if (i == 0 && ((cmd[0] != ' ') || (cmd[0] == ' ' \
									&& g_cursor.position_line == 0)))
		i--;
	x = i + 1;
	len = 0;
	while (cmd[++i])
	{
		if (!quote && !inib && cmd[i] == ' ')
			break ;
		if (!quote && !inib && cmd[i] == '\\')
			inib = 1;
		else
		{
			quote = quote_norm(inib, quote, cmd[i]);
			if (is_a_word(quote, inib, cmd[i]))
				len++;
			inib = 0;
		}
	}
	if (!len)
		return (ft_strdup(""));
	return (cpy_inib_path(cmd + x, len, 0, 0));
}

t_liste		*get_list_completion(char *cmd, int i)
{
	t_liste		*list;
	char		*path;

	if ((path = get_inib_path(cmd, i, 0, 0)))
		replace_cmd_cur_word(path, cmd, i);
	list = NULL;
	if (binary_or_file(cmd, i, 0, 0) == 2)
		list = get_list_of_file_completion(path);
	else
		list = get_list_of_bin_completion(path);
	if (!list)
		return (NULL);
	print_nd_reset_cursor(list, g_cursor.position_line);
	g_shell.tab_lvl = 1;
	return (list);
}
