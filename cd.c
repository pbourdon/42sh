/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 11:10:04 by bde-maze          #+#    #+#             */
/*   Updated: 2016/05/23 09:02:23 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	writecdiftwo2(char *str)
{
	ft_putstr("cd: string not in pwd: ");
	ft_putendl(str);
}

void	freecdiftwo(char *str, char **dst)
{
	ft_strdel(&str);
	freetab(dst);
}

char	*cdiftwo(t_data *data)
{
	char	*str;
	char	**tabb;
	char	**dst;
	char	*ptr;
	int		i;

	i = 1;
	str = getpwd();
	if (ft_strstr(str, data->args[1]) != NULL)
	{
		tabb = ft_strsplit(str, '/');
		ptr = ft_joinfree("/", ft_strjoin(tabb[0], "/"), 2);
		dst = changeargs(tabb, data);
		while (dst[i])
		{
			ptr = ft_joinfree(ptr, dst[i], 1);
			if (dst[i + 1])
				ptr = ft_joinfree(ptr, "/", 1);
			i++;
		}
		freecdiftwo(str, dst);
		return (ptr);
	}
	writecdiftwo2(data->args[1]);
	data->binreturn = 255;
	return (str);
}

void	cdcall2(t_data *data, char *str)
{
	if (errcd(data) == 1)
	{
		str = joincd(str, data);
		chdir(str);
		if (str)
			ft_strdel(&str);
		changepwdenv(data);
		if (data->voldpwd)
			ft_strdel(&data->voldpwd);
		data->turn = 1;
	}
}

void	cdcall(t_data *data)
{
	char	*str;

	if (ft_strlentab(data->args) == 3)
	{
		str = cdiftwo(data);
		chdir(str);
		if (str)
			ft_strdel(&str);
		changepwdenv(data);
		if (data->voldpwd)
			ft_strdel(&data->voldpwd);
		data->turn = 1;
		return ;
	}
	else if (ft_strlentab(data->args) < 4)
	{
		str = NULL;
		cdcall2(data, str);
	}
	else
	  {
	  ft_putendl("cd: too many arguments");
	  data->binreturn = 255;
	  }
}
