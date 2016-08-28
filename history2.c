/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 13:52:23 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/28 13:53:23 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void			show_history_until(char *len)
{
	int			i;
	int			j;
	int			tmp;
	t_history	*history;

	i = 0;
	j = 0;
	tmp = ft_atoi(len);
	history = g_shell.history;
	while (history->next && j <= tmp)
	{
		ft_putnbr(i++);
		if (i <= 10)
			ft_putstr("     ");
		else if (i <= 100)
			ft_putstr("    ");
		else
			ft_putstr("   ");
		ft_putendl(history->str);
		history = history->next;
		j++;
	}
}

void			show_history(void)
{
	int			i;
	t_history	*history;

	i = 0;
	history = g_shell.history;
	while (history->next)
	{
		ft_putnbr(i++);
		if (i <= 10)
			ft_putstr("     ");
		else if (i <= 100)
			ft_putstr("    ");
		else
			ft_putstr("   ");
		ft_putendl(history->str);
		history = history->next;
	}
}

int				ft_strisdigit(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (0);
}
