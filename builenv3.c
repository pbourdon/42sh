/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builenv3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 14:43:22 by bde-maze          #+#    #+#             */
/*   Updated: 2016/10/22 10:30:01 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

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

int		intb2(t_data *data, char *str, char *dst, char **tabb)
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

void	deletefromenvtool(t_data *data, char **tabb, int k, int in)
{
	if (in == 1)
	{
		if (data->builttab)
		{
			freetab(data->builttab);
			if (tabb[0] == NULL)
				data->builttab = NULL;
			else
				data->builttab = newtab(tabb);
			freetab(tabb);
		}
	}
	if (data->args[k + 1])
		deletefromenv(data, k + 1, 0);
}

void	deletefromenv(t_data *data, int k, int o)
{
	int		i;
	char	**tabb;
	int		in;

	in = 0;
	o = 0;
	i = -1;
	if (!data->builttab || !data->builttab[0])
		return ;
	tabb = (char **)malloc(sizeof(char *) * (ft_strlentab(data->builttab) - 2));
	while (data->builttab[++i])
	{
		if (ft_strcmp(data->builttab[i], data->args[k]) == 0 && (in = 1) \
			&& !(i % 3))
		{
			if (data->builttab[i + 3])
				i = i + 3;
			else if (!(tabb[o] = NULL))
				return (deletefromenvtool(data, tabb, k, in));
		}
		tabb[o] = ft_strdup(data->builttab[i]);
		o++;
	}
	tabb[o] = NULL;
	deletefromenvtool(data, tabb, k, in);
}
