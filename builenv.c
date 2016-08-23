/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/23 12:43:50 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/23 19:37:05 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		ft_strlequal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*firstpartequal(char *str)
{
	int i;
	int length;
	char *dst;

	i = 0;
	length = ft_strlequal(str);
	dst = malloc(sizeof(char) * (length + 1));
	while (str[i] != '=' && str[i])
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*secondpartequal(char *str)
{
	int i;
	int o;
	char *dst;

	o = 0;
	i = ft_strlequal(str) + 1;
	dst = malloc(sizeof(char) * (ft_strlen(str) - i) + 1);
	while (str[i])
	{
		dst[o] = str[i];
		i++;
		o++;
	}
	dst[o] = '\0';
	return (dst);
}

char	**freshnewtab(t_data *data, char *dst, char *dst2)
{
	int i;
	char **tabb;

	i = 0;
	tabb = malloc(sizeof(char *) * (ft_strlentab(data->builttab) + 4));
	if (data->builttab)
	{
		while (data->builttab[i])
		{
			tabb[i] = ft_strdup(data->builttab[i]);
			i++;
		}
	}
	tabb[i] = ft_strdup(dst);
	free(dst);
	tabb[i + 1] = ft_strdup("=");
	tabb[i + 2] = ft_strdup(dst2);
	free(dst2);
	tabb[i + 3] = NULL;
	return (tabb);
}

int 	alreadyintb(t_data *data, char *str, char *dst)
{
	int i;
	char **tabb;
	int o;

	o = -1;
	tabb = malloc(sizeof(char *) * (ft_strlentab(data->builttab) + 1));
	i = 0;
	if (data->builttab)
	{
		while (data->builttab[i])
		{
			if ((ft_strcmp(data->builttab[i], str)  == 0) && ((i % 3) == 0))
			{
				tabb[i] = ft_strdup(str);
				tabb[i + 1] = ft_strdup("=");
				tabb[i + 2] = ft_strdup(dst);
				if (data->builttab[i + 3] == NULL)
				{
					tabb[i + 3] = NULL;
					freetab(data->builttab);
					data->builttab = newtab(tabb);
					return (o);
				}
				i = i + 3;
				o = 1;
			}
			tabb[i] = ft_strdup(data->builttab[i]);
			i++;
		}
		i = 0;
		freetab(data->builttab);
		data->builttab = newtab(tabb);
		return (o);
	}
	return (-1);
}

int		checklineok(t_data *data, char **tabb)
{
	int i;
	char *dst;
	char *dst2;

	i = 0;
	if (ft_strlentab(tabb) != 1)
		return (-1);
	if (ft_strstr(tabb[0], "=") != NULL)
	{
		dst = firstpartequal(tabb[0]);
		dst2 = secondpartequal(tabb[0]);
		if (alreadyintb(data, dst, dst2) == -1)
			data->builttab = freshnewtab(data, dst, dst2);
		return (1);
	}
	return (-1);
}

char	**modiftabafteruse(t_data *data)
{
	int i;
	char **tabb;
	int o;

	o = 0;
	tabb = malloc(sizeof(char *) * (ft_strlentab(data->builttab) - 2));
	i = 0;
	while (data->builttab[i])
	{
		if (ft_strcmp(data->builttab[i], data->args[1]) == 0)
		{
			if (data->builttab[i + 3])
				i = i + 3;
			else
				{
					tabb[o] = NULL;
					freetab(data->builttab);
					return (tabb);
				}
		}
		tabb[o] = ft_strdup(data->builttab[i]);
		i++;
		o++;
	}
	tabb[o] = NULL;
	freetab(data->builttab);
	return (tabb);
}

int		insertthetmp(t_data *data)
{
	char *str;
	int i;

	i = 0;
	if (data->builttab)
	{
		while (data->builttab[i])
		{
			if (ft_strcmp(data->builttab[i], data->args[1]) == 0)
			{
				str = ft_strjoin(data->builttab[i], "=");
				str = ft_strjoin(str, data->builttab[i + 2]);
				str = ft_strjoin("setenv ", str);
				data->builttab = modiftabafteruse(data);
				data->args = ft_strsplit(str, ' ');
				callsetenv(data);
				return (1);
			}
			i += 3;
		}
	}
	return (1);
}
