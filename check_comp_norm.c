/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_comp_norm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 12:05:54 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/21 16:44:34 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		free_list_loop(void)
{
	t_liste *tmp;
	t_liste *list;
	t_liste *b;

	if (!g_shell.tab_lst)
		return ;
	b = g_shell.tab_lst;
	list = g_shell.tab_lst->next;
	while (list != b)
	{
		tmp = list;
		list = list->next;
		ft_memdel((void **)&tmp->arg);
		tmp->next = NULL;
		ft_memdel((void **)&tmp);
	}
	tmp = list;
	list = list->next;
	ft_memdel((void **)&tmp->arg);
	tmp->next = NULL;
	ft_memdel((void **)&tmp);
	g_shell.tab_lst = NULL;
}

void		check_comp_norm(char *buffer)
{
	if (is_tab(buffer))
		press_tab_key();
	else
	{
		if (g_shell.tab_lvl)
			tputs(tgetstr("cd", NULL), 0, tputs_putchar);
		g_shell.tab_lvl = 0;
		free_list_loop();
	}
}
