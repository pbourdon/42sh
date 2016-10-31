/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all_pid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 03:45:15 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/06 03:45:56 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		kill_func(t_data *data)
{
	pid_t		father;
	t_liste2	*liste;
	int			d;

	d = 0;
	liste = data->liste;
	if ((father = fork()) == 0)
	{
		while (liste)
		{
			if (!d && !kill(liste->pid, 0))
				d = liste->pid;
			if (d && kill(liste->pid, 0) == -1)
			{
				kill(d, 2);
				d = 0;
				liste = data->liste;
			}
			else if (!liste->next && d && !(d = 0))
				liste = data->liste;
			else
				liste = liste->next;
		}
		exit(0);
	}
}

int			wait_fcnt(t_data *data, t_liste2 *l)
{
	int status;
	int tmp;

	tmp = 0;
	status = 0;
	if (l->next)
		status = wait_fcnt(data, l->next);
	else if (!l->pid)
		exit(255);
	else if (!l->next)
	{
		waitpid(l->pid, &status, 0);
		return (status);
	}
	waitpid(l->pid, &tmp, 0);
	return (status);
}

void		wait_all_pid(t_data *data)
{
	t_liste2	*liste;
	int			status;
	int			nb;

	liste = data->liste;
	status = 0;
	nb = 0;
	kill_func(data);
	if ((status = wait_fcnt(data, data->liste)))
		exit(1);
	exit(0);
}
