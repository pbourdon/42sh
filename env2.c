/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:47:46 by hlouar            #+#    #+#             */
/*   Updated: 2016/05/23 09:11:47 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	callenvitools(t_data *data, char **tabb, int i)
{
	if (data->fona == 1)
		freetab(tabb);
	else
		free(tabb);
	data->envi = 1;
	argsifenv(data, i);
	forkall(data, 0);
}

void	callenvi(t_data *data)
{
	int		i;
	char	**tabb;

	i = 2;
	tabb = (char **)malloc(sizeof(char *) * ft_strlentab(data->args) + 1);
	data->fona = 0;
	while (data->args[i])
	{
		if (ft_strstr(data->args[i], "=") != NULL)
		{
			tabb[i - 2] = ft_strdup(data->args[i]);
			data->fona = 1;
		}
		else
		{
			tabb[i - 2] = NULL;
			callenvitools(data, tabb, i);
			return ;
		}
		i++;
	}
	tabb[i - 2] = NULL;
	printab(tabb);
	freetab(tabb);
	data->envi = 0;
}

void	callallenv(t_data *data)
{
	if (ft_strcmp(data->args[1], "-i") == 0)
		callenvi(data);
	else
		callenv(data);
}
