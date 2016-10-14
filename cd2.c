/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 18:08:14 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/14 23:47:17 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	add_opwd(t_data *data, char *opwd)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (ft_strlentab(data->env) + 2));
	i = -1;
	while (data->env[++i])
		new[i] = ft_strdup(data->env[i]);
	new[i] = ft_strjoin("OLDPWD=", opwd);
	data->voldpwd = opwd;
	new[++i] = NULL;
	freetab(data->env);
	data->env = new;
}

void	to_set_opwd(t_data *data)
{
	int		i;
	char	*str;
	char	**tabb;
	char	*pwd;

	str = getpwd();
	if (!str)
		str = ft_strdup("/");
	if (str == NULL)
		str = ft_strdup("/");
	tabb = data->env;
	i = -1;
	pwd = NULL;
	while (tabb[++i])
	{
		if (!ft_strncmp(tabb[i], "OLDPWD=", 7))
		{
			free(tabb[i]);
			tabb[i] = ft_strjoin("OLDPWD=", str);
			ft_memdel((void **)&str);
			return ;
		}
	}
	return (add_opwd(data, str));
}

void	gethome(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strstr(data->env[i], "HOME=") != NULL)
		{
			data->home = ft_strsub(data->env[i], 5, ft_strlen(data->env[i]));
			return ;
		}
		i++;
	}
	data->home = NULL;
}
