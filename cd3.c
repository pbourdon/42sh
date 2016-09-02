/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 08:57:51 by bde-maze          #+#    #+#             */
/*   Updated: 2016/05/23 09:04:27 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char	*joincd2(char *str, t_data *data)
{
	if (ft_strlentab(data->args) == 1)
	{
		if (data->home != NULL)
			str = ft_strdup(data->home);
		else
			str = getpwd();
		return (str);
	}
	else if (ft_strcmp(data->args[1], "-") == 0)
	{
		if (data->voldpwd)
			str = ft_strdup(data->voldpwd);
		else
			str = getpwd();
		return (str);
	}
	else if (data->args[1][0] == '/')
	{
		str = "/";
		str = ft_joinfree(str, data->args[1], 0);
		return (str);
	}
	return (str);
}

char	*joincd(char *str, t_data *data)
{
	if ((ft_strlentab(data->args) == 1) ||
			(ft_strcmp(data->args[1], "-") == 0) ||
			data->args[1][0] == '/')
	{
		str = joincd2(str, data);
		return (str);
	}
	else
	{
		str = getpwd();
		if (str != NULL)
		{
			str = ft_joinfree(str, "/", 1);
			str = ft_joinfree(str, data->args[1], 1);
		}
		return (str);
	}
	str = NULL;
	return (str);
}

void	writeerrcd(char *str)
{
	struct stat sb;

	stat(str, &sb);
	if ((S_ISREG(sb.st_mode)))
	{
		ft_putstr("cd: not a directory: ");
		ft_putendl(str);
	}
	else
	{
		ft_putstr("cd: not such file or directory: ");
		ft_putendl(str);
	}
}

int		errcd(t_data *data)
{
	char	*str;
	DIR		*rep;

	str = NULL;
	str = joincd(str, data);
	rep = opendir(str);
	if (rep == NULL)
	{
		writeerrcd(data->args[1]);
		free(str);
		return (-1);
	}
	closedir(rep);
	free(str);
	return (1);
}

char	**changeargs(char **tabb, t_data *data)
{
	int		i;
	char	**dst;
	int		o;

	o = 0;
	dst = (char **)malloc(sizeof(char *) * (ft_strlentab(tabb) + 1));
	i = 0;
	while (tabb[i])
	{
		if (ft_strcmp(tabb[i], data->args[1]) == 0)
		{
			dst[o] = ft_strdup(data->args[2]);
			o++;
			i++;
		}
		dst[o] = ft_strdup(tabb[i]);
		i++;
		o++;
	}
	dst[o] = NULL;
	freetab(tabb);
	return (dst);
}
