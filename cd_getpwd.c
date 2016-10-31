/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_getpwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 18:09:06 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/14 23:47:29 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char	*getpwd(void)
{
	char	*tmp;
	char	*dst;

	tmp = ft_memalloc(1024);
	if (getcwd(tmp, 1024) != NULL)
	{
		dst = ft_strdup(tmp);
		ft_strdel(&tmp);
		return (dst);
	}
	return (NULL);
}

void	add_pwd(t_data *data, char *pwd)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (ft_strlentab(data->env) + 2));
	i = -1;
	while (data->env[++i])
		new[i] = ft_strdup(data->env[i]);
	new[i] = ft_strjoin("PWD=", pwd);
	new[++i] = NULL;
	freetab(data->env);
	data->env = new;
	free(pwd);
}

void	to_set_pwd(t_data *data)
{
	int		i;
	char	*str;
	char	**tabb;
	char	*pwd;

	str = getpwd();
	if (str == NULL)
		ft_strdup("/");
	tabb = data->env;
	i = -1;
	pwd = NULL;
	while (tabb[++i])
	{
		if (!ft_strncmp(tabb[i], "PWD=", 4))
		{
			free(tabb[i]);
			tabb[i] = ft_strjoin("PWD=", str);
			if (data->pwd)
				free(data->pwd);
			data->pwd = str;
			return ;
		}
	}
	return (add_pwd(data, str));
}
