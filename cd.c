/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 11:10:04 by hlouar            #+#    #+#             */
/*   Updated: 2016/05/23 09:02:23 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	writecdiftwo2(char *str)
{
	ft_putstr("cd: string not in pwd: ");
	ft_putendl(str);
}

void	freecdiftwo(char *str, char **dst)
{
	free(str);
	freetab(dst);
}

char	*cdiftwo(t_data *data)
{
	char	*str;
	char	**tab;
	char	**dst;
	char	*ptr;
	int		i;

	i = 1;
	str = getpwd();
	if (ft_strstr(str, data->args[1]) != NULL)
	{
		tab = ft_strsplit(str, '/');
		ptr = ft_joinfree("/", ft_strjoin(tab[0], "/"), 2);
		dst = changeargs(tab, data);
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
	return (str);
}

void	cdcall2(t_data *data, char *str)
{
	if (errcd(data) == 1)
	{
		str = joincd(str, data);
		chdir(str);
		if (str)
			free(str);
		changepwdenv(data);
		if (data->voldpwd)
			free(data->voldpwd);
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
			free(str);
		changepwdenv(data);
		if (data->voldpwd)
			free(data->voldpwd);
		data->turn = 1;
		return ;
	}
	else if (ft_strlentab(data->args) < 4)
	{
		str = NULL;
		cdcall2(data, str);
	}
	else
		ft_putendl("cd: too many arguments");
}