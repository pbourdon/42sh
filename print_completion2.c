/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 10:54:07 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/21 10:55:07 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		reset_cursor(int l, int cp)
{
	int len;
	int qw;

	qw = -1;
	len = g_shell.shell_win_size;
	while (l > 0)
	{
		tputs(tgetstr("up", NULL), 0, tputs_putchar);
		l--;
	}
	qw = ((g_cursor.position_line + 6) % len) + 1;
	while (--qw)
	{
		tputs(tgetstr("nd", NULL), 0, tputs_putchar);
	}
	while (g_cursor.position_line != cp)
		press_left_key();
	g_shell.tab_lvl = 1;
}

void		print_nd_reset_cursor(t_liste *list, int cp)
{
	int max;
	int col;
	int l;
	int shell_size;

	if ((max = get_max_and_close_circular_chainlist(list)) &&
		(shell_size = g_shell.shell_win_size - 1))
		col = shell_size / (max + 8);
	else
		col = 1;
	g_shell.tab_lst = list;
	g_shell.tab_lvl = 1;
	cp = g_cursor.position_line;
	l = print_padded_list(list, col, max) + 1;
	return (reset_cursor(l, cp));
}
