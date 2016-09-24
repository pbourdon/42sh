/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 11:10:04 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/21 17:56:07 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	writecdiftwo2(char *str)
{
	ft_putstr_fd("cd: string not in pwd: ", 2);
	ft_putendl_fd(str, 2);
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

	str = getpwd();
	if ((i = 1) && ft_strstr(str, data->args[1]) != NULL)
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
		to_set_opwd(data);
		chdir(str);
		if (str)
			ft_strdel(&str);
		to_set_pwd(data);
		if (data->voldpwd)
			ft_strdel(&data->voldpwd);
		data->turn = 1;
	}
}
