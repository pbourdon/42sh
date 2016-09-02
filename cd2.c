/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 08:56:01 by bde-maze          #+#    #+#             */
/*   Updated: 2016/05/23 09:03:27 by bde-maze         ###   ########.fr       */
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
		free(tmp);
		return (dst);
	}
	return (NULL);
}

char	*changepwd3(t_data *data, char *str, char *str2)
{
	if (data->oldpwd)
		data->voldpwd = ft_strdup(data->oldpwd);
	else
		data->voldpwd = ft_strdup(str2);
	if (data->oldpwd)
		str = ft_strjoin("OLDPWD=", data->oldpwd);
	else
		str = ft_strjoin("OLDPWD=", str2);
	return (str);
}

char	**changepwd2(t_data *data, char **tabb, char *str)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	while (data->env[i])
	{
		if (rognagestring(data->env[i], "PWD=") == 1)
		{
			tabb[o] = ft_strjoin("PWD=", str);
			o++;
			i++;
		}
		else if (rognagestring(data->env[i], "OLDPWD=") == 1)
		{
			tabb[o] = changepwd3(data, tabb[o], str);
			o++;
			i++;
		}
		tabb[o] = ft_strdup(data->env[i]);
		o++;
		i++;
	}
	tabb[o] = NULL;
	return (tabb);
}

void	changepwdenv(t_data *data)
{
	int		i;
	char	**tabb;
	int		o;
	char	*str;

	str = getpwd();
	o = 0;
	tabb = (char **)malloc(sizeof(char *) * (ft_strlentab(data->env) + 1));
	i = 0;
	tabb = changepwd2(data, tabb, str);
	if (data->turn == 1)
		freetab(data->env);
	data->env = newtab(tabb);
	freetab(tabb);
	free(str);
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
