/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testredi5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 16:04:05 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/16 16:04:08 by hlouar           ###   ########.fr       */
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
