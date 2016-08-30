/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/30 11:08:51 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/30 11:08:52 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		movecd(t_data *data)
{
	t_liste2 *tmp;
	int out;

	tmp = data->liste;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->tabich[0], "cd") == 0)
		{
			if ((tmp->redi == 2 && tmp->next->redi == 0)
			|| (tmp->redi == 1 && tmp->next->redi == 0)
			|| (tmp->redi == 3 && (tmp->next->redi != 5))
			|| (tmp->redi == 4 && (tmp->next->redi != 5))
			|| (tmp->redi == 0))
			{
				if (tmp->redi == 1)
				{
					out = open(tmp->next->tabich[0], O_WRONLY | O_TRUNC |
						O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR | O_APPEND);
				}
				else if (tmp->redi == 2)
				{
						out = open(tmp->next->tabich[0], O_RDWR);
						if (out == -1)
						{
							out = open(tmp->next->tabich[0], O_WRONLY | O_TRUNC |
								O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR | O_APPEND);
						}
				}
					data->args = newtab(tmp->tabich);
					cdcall(data);
					return (2);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
