/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_tab_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 10:35:31 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/21 10:46:00 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		set_cur_end_word(char *cmd, int b_word)
{
	int i;
	int quote;
	int inib;

	i = b_word;
	if (b_word == 0)
		i--;
	inib = 0;
	quote = 0;
	while (cmd[++i])
	{
		if (!quote && !inib && cmd[i] == '\\')
			inib = 1;
		else
		{
			quote = quote_norm(inib, quote, cmd[i]);
			if (cmd[i] == ' ' && !inib && !quote)
				break ;
			inib = 0;
		}
		if (i == g_cursor.position_line)
			press_right_key();
	}
}

int			is_only_space(char *cmd)
{
	int i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] != ' ')
			return (0);
	}
	return (1);
}

int			find_begin_word(char *cmd, int cur, int quote, int inib)
{
	int beg;
	int swap;
	int i;

	swap = 0;
	beg = 0;
	i = -1;
	while (++i != cur)
	{
		if (!quote && !inib && cmd[i] == '\\')
			inib = 1;
		else
		{
			quote = quote_norm(inib, quote, cmd[i]);
			if (!quote && !inib && cmd[i] == ' ')
				beg = i;
			inib = 0;
		}
	}
	return (beg);
}

void		press_tab_key(void)
{
	int		i;
	char	*cmd;
	t_liste *list;

	list = NULL;
	cmd = g_shell.shell_line;
	if (!(g_shell.length_line) || is_only_space(cmd))
		return ;
	i = find_begin_word(cmd, g_cursor.position_line, 0, 0);
	if (g_shell.tab_lvl == 0)
	{
		if (!(list = get_list_completion(cmd, i)))
			return ;
	}
	else if (g_shell.tab_lvl == 1)
	{
		replace_cmd_cur_word(g_shell.tab_lst->arg, cmd, i);
		list = g_shell.tab_lst;
		print_nd_reset_cursor(g_shell.tab_lst, g_cursor.position_line);
		g_shell.tab_lst = g_shell.tab_lst->next;
	}
}
