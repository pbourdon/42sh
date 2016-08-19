/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testredi3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 15:26:37 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/17 16:24:34 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		refredi(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return (1);
	else if (ft_strcmp(str, ">>") == 0)
		return (2);
	else if (ft_strcmp(str, "<") == 0)
		return (3);
	else if (ft_strcmp(str, "<<") == 0)
		return (4);
	else if (ft_strcmp(str, "|") == 0)
		return (5);
	else if (checkagred(str) == 1)
		return (6);
	return (0);
}

int		lastone(t_data *data)
{
	int	length;

	length = ft_strlentab(data->oldtbe);
	while (length > 0)
	{
		if (ft_strcmp(data->oldtbe[length], "|") == 0)
			return (length);
		length--;
	}
	return (-1);
}

int		pospipe(t_data *data, int i)
{
	while (data->oldtbe[i])
	{
		if ((ft_strcmp(data->oldtbe[i], "|") == 0) ||
				(ft_strcmp(data->oldtbe[i], "<") == 0))
		{
			ft_putnbr(i);
			data->posi = i + 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	argliste(t_data *data)
{
	int		i;
	int		k;
	t_liste2	*tmp;

	tmp = data->liste;
	k = lastone(data);
	i = 0;
	while (data->posi != ft_strlentab(data->oldtbe))
	{
		if (i == 0)
		{
			tmp->tabich = createtab(data, 0);
			i = 1;
		}
		else
			tmp->tabich = createtab(data, data->posi + 1);
		if (data->oldtbe[data->posi])
			tmp->redi = refredi(data->oldtbe[data->posi]);
		else
			tmp->redi = 0;
		tmp->next = malloc(sizeof(t_liste2));
		tmp = tmp->next;
		tmp->next = NULL;
	}
}

void	freeliste(t_liste2 *liste)
{
	while (liste->next->next != NULL)
	{
		freetab(liste->tabich);
		liste = liste->next;
	}
	free(liste);
}
