/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builenv3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 14:43:22 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/24 14:48:17 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		alreadyin(t_data *data, char *str)
{
	int i;

	i = 0;
	if (data->builttab)
	{
		while (data->builttab[i])
		{
			if ((ft_strcmp(data->builttab[i], str) == 0) && ((i % 3) == 0))
				return (1);
			i++;
		}
		return (0);
	}
	return (0);
}

void	alreadyintb3(t_data *data, char **tabb)
{
	freetab(data->builttab);
	data->builttab = newtab(tabb);
	freetab(tabb);
}

int		alreadyintb2(t_data *data, char *str, char *dst, char **tabb)
{
	int i;

	i = 0;
	while (data->builttab[i])
	{
		if ((ft_strcmp(data->builttab[i], str) == 0) && ((i % 3) == 0))
		{
			tabb[i] = ft_strdup(str);
			tabb[i + 1] = ft_strdup("=");
			tabb[i + 2] = ft_strdup(dst);
			if (data->builttab[i + 3] == NULL)
			{
				tabb[i + 3] = NULL;
				alreadyintb3(data, tabb);
				return (1);
			}
			i = i + 3;
		}
		tabb[i] = ft_strdup(data->builttab[i]);
		i++;
	}
	tabb[i] = NULL;
	alreadyintb3(data, tabb);
	return (1);
}
