/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:47:46 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/21 23:56:56 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		env_var_exist(char *str, char **env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		tmp = ft_strchr(env[i], '=');
		*tmp = 0;
		if (!ft_strcmp(str, env[i]))
		{
			*tmp = '=';
			return (i);
		}
		*tmp = '=';
	}
	return (-1);
}

char	**fill_env_var_norm(char **new, char **tabb, int j, int i)
{
	int		t;
	char	*tmp;

	while (tabb[i] && (tmp = ft_strchr(tabb[i], '=')))
	{
		*tmp = 0;
		if (env_var_exist(tabb[i], new) == -1)
		{
			*tmp = '=';
			new[++j] = ft_strdup(tabb[i]);
			new[j + 1] = NULL;
		}
		else if ((t = env_var_exist(tabb[i], new)) > -1)
		{
			free(new[t]);
			*tmp = '=';
			new[t] = ft_strdup(tabb[i]);
		}
		*tmp = '=';
		i++;
	}
	return (new);
}

char	**fill_env_var(char **new, char **env, char **tabb)
{
	int		i;
	int		j;
	int		t;
	char	*tmp;

	j = -1;
	i = 1;
	while (env[++j])
		new[j] = ft_strdup(env[j]);
	new[j] = NULL;
	while (tabb[i] && (tmp = ft_strchr(tabb[i], '=')))
	{
		*tmp = 0;
		if ((t = env_var_exist(tabb[i], new)) > -1)
		{
			free(new[t]);
			*tmp = '=';
			new[t] = ft_strdup(tabb[i]);
		}
		*tmp = '=';
		i++;
	}
	return (fill_env_var_norm(new, tabb, j - 1, 1));
}

char	**get_var(char **tabb)
{
	int		i;
	int		len;
	char	**new;

	i = 2;
	len = 0;
	while (tabb[i] && ft_strchr(tabb[i], '='))
	{
		len++;
		i++;
	}
	new = (char **)malloc(sizeof(char *) * (len + 1));
	i = 2;
	len = -1;
	new[0] = NULL;
	new = fill_env_var_norm(new, tabb, -1, 2);
	return (new);
}

char	**get_env_nd_var(char **tabb, char **env)
{
	int		i;
	int		len;
	char	*tmp;
	char	**new;

	len = 0;
	i = 1;
	while (tabb[i] && (tmp = ft_strchr(tabb[i], '=')))
	{
		*tmp = 0;
		if (env_var_exist(tabb[i], env) == -1)
			len++;
		*tmp = '=';
		i++;
	}
	len += ft_strlentab(env);
	new = (char **)malloc(sizeof(char *) * (len + 1));
	new = fill_env_var(new, env, tabb);
	return (new);
}
