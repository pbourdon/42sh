/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 10:40:39 by hlouar            #+#    #+#             */
/*   Updated: 2016/05/23 09:25:30 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		existornah(char **tab, char *str)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		if (rognagestring(tab[i], str) == 1)
			return (1);
		i++;
	}
	return (0);
}

char	**printifenv2(char **tab, char *str)
{
	int		i;
	int		o;
	char	**dst;

	dst = (char **)malloc(sizeof(char *) * (ft_strlentab(tab) + 2));
	i = 0;
	o = 0;
	while (tab[i] != NULL)
	{
		dst[o] = ft_strdup(tab[i]);
		o++;
		i++;
	}
	dst[o] = ft_strdup(str);
	dst[o + 1] = NULL;
	freetab(tab);
	return (dst);
}

char	**callenvtool2(char **tab, t_data *data, int i)
{
	if (existornah(tab, data->args[i]) == 1)
		tab = printifenv(tab, data->args[i]);
	else
		tab = printifenv2(tab, data->args[i]);
	return (tab);
}

void	callenv(t_data *data)
{
	int		i;
	char	**tab;

	i = 1;
	tab = newtab(data->env);
	if (ft_strcmp(data->line, "env") == 0)
	{
		freetab(tab);
		printab(data->env);
		return ;
	}
	while (data->args[i])
	{
		if (ft_strstr(data->args[i], "=") != NULL)
			tab = callenvtool2(tab, data, i);
		else
		{
			freetab(tab);
			argsifenv(data, i);
			forkall(data);
			return ;
		}
		i++;
	}
	callenvtool(data, tab);
}
