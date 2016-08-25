/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testredi5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 16:04:05 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/25 16:18:25 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		helpall2(t_data *data, t_liste2 *liste)
{
	int	out;

	out = open(liste->next->tabich[0], O_WRONLY | O_TRUNC |
			O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR | O_APPEND);
	dup2(out, 1);
	close(out);
	freetab(data->args);
	data->args = newtab(liste->tabich);
	execveremix(data);
	return (1);
}

void	printtab(char **tabb)
{
	int i;

	i = 0;
	ft_putendl("_______TAB________");
	while (tabb[i] != NULL)
	{
		ft_putendl(tabb[i]);
		i++;
	}
	ft_putendl("_______TAB________");
}

int		hulppls(t_data *data, t_liste2 *liste, int pfd[2])
{
	freetab(data->args);
	data->args = newtab(liste->tabich);
	if (createbinpath(data, 2) == 0)
	{
		ft_putstr(data->args[0]);
		ft_putendl(": Command not found");
		exit(0);
	}
	dup2(pfd[1], 1);
	close(pfd[0]);
	if (execveremix(data) == -1)
		exit(0);
	return (1);
}

int		printerrred(t_liste2 *tmp)
{
	ft_putstr(tmp->tabich[0]);
	ft_putendl(": Command not found");
	return (1);
}

void	helpagreve(t_data *data, int a, int b, t_liste2 *liste)
{
	if (ft_strstr(data->oldtbe[ft_strlentab(data->oldtbe) - 1], "<") != NULL)
		dup2(a, b);
	else
		dup2(b, a);
	freetab(data->args);
	data->args = newtab(liste->tabich);
	execveremix(data);
}
