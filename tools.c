/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 18:45:14 by hlouar            #+#    #+#             */
/*   Updated: 2016/05/19 17:24:58 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		ft_strlenremix(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
	{
		i++;
	}
	return (i);
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
	tab = NULL;
}

void	freetab2(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
	{
		ft_strdel(&(data->env[i]));
		i++;
	}
	free(data->env);
	data->env = NULL;
}

int		ft_strlentab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return (-1);
	while (tab[i] != NULL)
		i++;
	return (i);
}

char	**newtab(char **tab)
{
	char	**dst;
	int		i;

	dst = (char **)malloc(sizeof(char *) * (ft_strlentab(tab) + 1));
	i = 0;
	while (tab[i])
	{
		dst[i] = ft_strdup(tab[i]);
		i++;
	}
	dst[i] = NULL;
	return (dst);
}
