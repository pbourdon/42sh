/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 15:22:47 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/25 14:20:54 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		helpmainpipehelp2(t_data *data, t_liste2 *liste, int k)
{
	int in;

	in = -1;
	if (k == 1)
	{
		in = open(liste->next->tabich[0], O_RDONLY);
	}
	else if (k == 2)
		in = open(".file_for_ready", O_RDONLY);
	if (in == -1)
	{
		ft_putstr("21sh: no such file or directory: ");
		ft_putendl(liste->next->tabich[0]);
		exit(0);
	}
	if (in == -1)
		exit(1);
	dup2(in, 0);
	close(in);
	doubleredichieh(data, liste, 0);
	if (data->tabchev)
		freetab(data->tabchev);
	return ;
}

void		help_dbl(t_data *data, int i, t_liste2 *liste, int fd)
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

int			optchev(t_data *data)
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

void		sub_exec(t_data *data)
{
	if (ft_strcmp(data->args[0], "exit") == 0)
		exit(0);
	if (ft_strcmp(data->args[0], "env") == 0)
	{
		callallenv(data);
		exit(0);
	}
}

int			execveremix(t_data *data)
{
	if (createthetab(data) == 1)
	{
		if (access(data->tabb[0], F_OK) == 0)
		{
			ft_reset_term(g_shell.term_reset.term_copy);
			if (data->envi == 1)
				execve(data->tabb[0], data->tabb, NULL);
			else
			{
				execve(data->tabb[0], data->tabb, data->env);
				ft_reset_term(g_shell.term_reset.term);
				return (1);
			}
			ft_reset_term(g_shell.term_reset.term);
		}
		freetab(data->tabb);
		freetab(data->args);
		return (-2);
	}
	return (-1);
}
