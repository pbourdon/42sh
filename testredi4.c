/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testredi4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 16:05:50 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/18 17:40:04 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	childhelp(t_data *data, t_liste2 *liste, int pfd[2])
{
	int in;

	if (liste->redi == 3 || liste->redi == 8)
	{
		if (liste->redi == 8)
			in = open(".file_for_ready", O_RDONLY);
		else
			in = open(liste->next->tabich[0], O_RDONLY);
		if (in == -1)
		{
			ft_putstr(liste->next->tabich[0]);
			ft_putendl(": No such file or directory.");
			return ;
		}
		dup2(in, 0);
	}
	hulppls(data, liste, pfd);
}

int		doubleredichieh(t_data *data, t_liste2 *liste)
{
	int		father;
	int		out;
	char	*str;
	int		fd;
	int		i;

	i = 0;
	father = fork();
	str = ft_strdup(data->args[(ft_strlentab(data->args) - 1)]);
	fd = open(str, O_RDWR);
	if (father == 0)
	{
		out = open(str, O_WRONLY | O_TRUNC |
		O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR | O_APPEND |
		S_IRWXO);
		dup2(out, 1);
		close(out);
		help_dbl(data, i, liste, fd);
		exit(0);
	}
	else
		wait(0);
	return (5);
}

int		helpall(t_data *data, t_liste2 *liste, int k)
{
	int	in;

	in = -1;
	if (k == 1)
		in = open(liste->next->tabich[0], O_RDONLY);
	else if (k == 2)
		in = open(".file_for_ready", O_RDONLY);
	if (in == -1)
		exit(1);
	dup2(in, 0);
	close(in);
	freetab(data->args);
	data->args = newtab(liste->tabich);
	execveremix(data);
	return (1);
}

int		mainpipehelp3(t_data *data, t_liste2 *liste)
{
	int	out;

	if (liste->next->redi == 1)
	{
		out = open(liste->next->next->tabich[0], O_WRONLY | O_TRUNC |
				O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR | O_APPEND);
		dup2(out, 1);
		close(out);
	}
	else if (liste->next->redi == 2)
	{
		if (liste->redi == 3)
			helpmainpipehelp2(data, liste, 1);
		else
			helpmainpipehelp2(data, liste, 2);
		return (10);
	}
	return (-1);
}

int		mainpipehelp2(t_data *data, t_liste2 *liste)
{
	if ((liste->redi == 3 || liste->redi == 8) && ((liste->next->redi == 0) ||
				((liste->next->redi == 1 || liste->next->redi == 2) &&
				liste->next->next->redi == 0)))
	{
		if (mainpipehelp3(data, liste) == 10)
			return (10);
		if (liste->redi == 3)
			helpall(data, liste, 1);
		else
			helpall(data, liste, 2);
		return (1);
	}
	return (-1);
}
