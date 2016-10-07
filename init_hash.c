/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 05:33:35 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/07 18:02:15 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int			get_len_tabhash(char *path)
{
	struct dirent	*ent;
	DIR				*dir;
	char			*tmp;
	int				l;

	l = 0;
	if ((dir = opendir(path)) == NULL)
		return (0);
	while ((ent = readdir(dir)))
		if (ft_strcmp(ent->d_name, ".") && ft_strcmp(ent->d_name, ".."))
		{
			tmp = ft_str2join(path, "/", ent->d_name);
			if (!access(tmp, F_OK | X_OK) || !access(tmp, F_OK | W_OK))
				l++;
			ft_strdel(&tmp);
		}
	closedir(dir);
	return (l);
}

void		err_long_path(char *envpath, char *tmp)
{
	int i;

	i = -1;
	ft_putendl_fd("TOO LONG PATH :", 2);
	ft_putendl_fd(envpath + 5, 2);
	ft_putendl_fd("cut to", 2);
	while (tmp[++i])
		tmp[i] = 0;
	ft_putendl_fd(envpath + 5, 2);
}

char		**search_true_binpath(char **path, char *envpath)
{
	int		i;
	int		len;
	int		size;
	char	*tmp;

	path = ft_strsplit((envpath + 5), ':');
	i = -1;
	size = 0;
	while (path[++i])
	{
		len = get_len_tabhash(path[i]);
		if (size + len > 2048)
		{
			tmp = envpath + 5;
			while (i--)
				tmp = ft_strchr(tmp + 1, ':');
			err_long_path(envpath, tmp);
			free_new_env(path);
			return (ft_strsplit(envpath + 5, ':'));
		}
		size += len;
	}
	return (path);
}

void		init_hashtab_norm(t_data *data, char **env, char **tabhash, int i)
{
	char	**path;

	path = NULL;
	path = search_true_binpath(path, env[i]);
	data->binpath = ft_strdup(env[i] + 5);
	i = -1;
	while (path && path[++i])
	{
		if (!access(path[i], F_OK | X_OK) || !access(path[i], F_OK | W_OK))
			tabhash = init_fill_tab(tabhash, path[i], 0);
		ft_strdel(&path[i]);
	}
	free(path);
	get_tabhash(tabhash, 0);
}

void		init_hashtab(t_data *data, char **env, int i)
{
	char		**path;
	char		**tabhash;

	path = NULL;
	if (!(tabhash = (char **)malloc(sizeof(char *) * 4096)))
		return ;
	while (++i < 4096)
		tabhash[i] = NULL;
	i = 0;
	while (env && env[i] && ft_strncmp(env[i], "PATH=", 5))
		++i;
	if (!env[i] || !*(env[i] + 5))
	{
		get_tabhash(tabhash, 0);
		return ;
	}
	init_hashtab_norm(data, env, tabhash, i);
}
