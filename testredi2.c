/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testredi2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 15:26:21 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/19 13:14:17 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		ifitsredi(t_data *data)
{
	int i;

	i = 0;
	while (data->args[i] != NULL)
	{
		if (ft_strcmp(data->args[i], ">") == 0)
			return (1);
		if (ft_strcmp(data->args[i], ">>") == 0)
			return (2);
		if (ft_strcmp(data->args[i], "<") == 0)
			return (3);
		if (ft_strcmp(data->args[i], "<<") == 0)
			return (4);
		if (ft_strcmp(data->args[i], "|") == 0)
			return (5);
		if (checkagred(data->args[i], 0, 0) == 1)
			return (6);
		i++;
	}
	return (0);
}

int		ft_strlenremx(char **tabich, int i, char *c)
{
	while (tabich[i] != NULL)
	{
		if (ft_strcmp(tabich[i], c) == 0)
			return (i);
		i++;
	}
	return (i);
}

void	helpcreatetab(t_data *data, int i, char **tabich)
{
	freetab(data->args);
	data->args = newtab(tabich);
	data->posi = i;
}

int		allif(char *str)
{
	if ((ft_strcmp(str, "|") == 0) ||
		(ft_strcmp(str, ">") == 0) ||
		(ft_strcmp(str, ">>") == 0) ||
		(ft_strcmp(str, "<") == 0) ||
		(ft_strcmp(str, "<<") == 0) ||
		(checkagred(str, 0, 0) == 1))
		return (1);
	return (-1);
}

char	**createtab(t_data *data, int i)
{
	char	**tabich;
	int		length;
	int		o;

	o = 0;
	length = ft_strlenremx(data->oldtbe, i, "|");
	tabich = malloc(sizeof(char *) * (length + 1));
	while (data->oldtbe[i] != NULL)
	{
		if (allif(data->oldtbe[i]) == 1)
		{
			tabich[o] = NULL;
			helpcreatetab(data, i, tabich);
			return (tabich);
		}
		tabich[o] = ft_strdup(data->oldtbe[i]);
		i++;
		o++;
	}
	tabich[o] = NULL;
	helpcreatetab(data, i, tabich);
	return (tabich);
}
