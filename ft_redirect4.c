/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 15:22:47 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/14 15:23:12 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void helpmainpipehelp2(t_data *data, t_liste2 *liste)
{
	int in;

	in = open(liste->next->tabich[0], O_RDONLY);
	dup2(in, 0);
	close(in);
	doubleredichieh(data, liste);
	if (data->tabchev)
		freetab(data->tabchev);
	return ;
}

t_liste2	*createliste(void)
{
	t_liste2	*liste;

	liste = (t_liste2 *)malloc(sizeof(t_liste2));
	liste->next = NULL;
	return (liste);
}

void	helpdoublechieh(t_data *data, int i, t_liste2 *liste, int fd)
{
	if (fd == -1)
	{
		freetab(data->args);
		data->args = newtab(liste->tabich);
		execveremix(data);
	}
	else
	{
		while (data->tabchev[i])
		{
			ft_putendl(data->tabchev[i]);
			i++;
		}
		freetab(data->tabchev);
		data->args = newtab(liste->tabich);
		execveremix(data);
	}
}

int		optchev(t_data *data)
{
	int	i;

	i = 0;
	while (data->oldtbe[i])
	{
		if (ft_strcmp(data->oldtbe[i], ">>") == 0)
			return (1);
		i++;
	}
	return (0);
}

int		execveremix(t_data *data)
{
	if (createthetab(data) == 1)
	{
		if (access(data->tabb[0], F_OK) == 0)
		{
			if (data->envi == 1)
			{
				execve(data->tabb[0], data->tabb, NULL);
			}
			else
			{
				execve(data->tabb[0], data->tabb, data->env);
				return (1);
			}
		}
		freetab(data->tabb);
		freetab(data->args);
		return (0);
	}
	return (0);
}