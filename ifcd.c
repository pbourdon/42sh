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

int cdendargs(t_data *data)
{
	int i;

	i = ft_strlentab(data->oldtbe) - 1;
	while (data->oldtbe[i])
	{
		if ((ft_strcmp(data->oldtbe[i], ">") == 0) ||
		(ft_strcmp(data->oldtbe[i], ">>") == 0))
			return (-1);
		if (ft_strcmp(data->oldtbe[i], "|") == 0)
		{
			if (ft_strcmp(data->oldtbe[i + 1], "cd") == 0)
			{
				ft_putendl(data->oldtbe[i + 1]);
				return (i);
			}
			else
				return (-1);
		}
		i--;
	}
	return (0);
}

int	stringforcd(t_data *data)
{
	int i;
	char **dst;
	int o;

	o = 0;
	i =  cdendargs(data) + 1;
	if (i <= 0)
		return (-1);
	dst = malloc(sizeof(char) * i);
	while (data->oldtbe[i])
	{
		dst[o] = data->oldtbe[i];
		i++;
		o++;
	}
	dst[o] = NULL;
	data->args = newtab(dst);
	// freetab(dst);
	cdcall(data);
	return (0);
 }
