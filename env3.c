/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 09:24:52 by hlouar            #+#    #+#             */
/*   Updated: 2016/05/23 09:24:53 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	printab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_putendl(tab[i]);
		i++;
	}
}

void	freeargs(t_data *data, int i)
{
	int	n;

	n = 0;
	while (n < i)
	{
		free(data->args[n]);
		n++;
	}
}

void	argsifenv(t_data *data, int n)
{
	int		i;
	int		o;
	char	**dst;

	freeargs(data, n);
	i = n;
	o = 0;
	dst = (char **)malloc(sizeof(char *) * ft_strlentab(data->args));
	while (data->args[i])
	{
		dst[o] = data->args[i];
		o++;
		i++;
	}
	dst[o] = NULL;
	free(data->args);
	data->args = dst;
}

void	callenvtool(t_data *data, char **tab)
{
	(void)data;
	printab(tab);
	freetab(tab);
}

char	**printifenv(char **tab, char *str)
{
	int		i;
	int		o;
	char	**dst;

	dst = (char **)malloc(sizeof(char *) * (ft_strlentab(tab) + 1));
	i = 0;
	o = 0;
	while (tab[i] != NULL)
	{
		if (rognagestring(tab[i], str) == 1)
		{
			dst[o] = ft_strdup(str);
			o++;
			i++;
		}
		dst[o] = ft_strdup(tab[i]);
		o++;
		i++;
	}
	dst[o] = NULL;
	freetab(tab);
	return (dst);
}
