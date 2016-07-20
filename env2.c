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

#include "includes/minishell.h"

void	callenvitools(t_data *data, char **tab, int i)
{
	if (data->fona == 1)
		freetab(tab);
	else
		free(tab);
	data->envi = 1;
	argsifenv(data, i);
	forkall(data);
}

void	callenvi(t_data *data)
{
	int		i;
	char	**tab;

	i = 2;
	tab = (char **)malloc(sizeof(char *) * ft_strlentab(data->args) + 1);
	data->fona = 0;
	while (data->args[i])
	{
		if (ft_strstr(data->args[i], "=") != NULL)
		{
			tab[i - 2] = ft_strdup(data->args[i]);
			data->fona = 1;
		}
		else
		{
			tab[i - 2] = NULL;
			callenvitools(data, tab, i);
			return ;
		}
		i++;
	}
	tab[i - 2] = NULL;
	printab(tab);
	freetab(tab);
	data->envi = 0;
}

void	callallenv(t_data *data)
{
	if (ft_strcmp(data->args[1], "-i") == 0)
		callenvi(data);
	else
		callenv(data);
}
