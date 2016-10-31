/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 17:16:42 by bde-maze          #+#    #+#             */
/*   Updated: 2016/10/07 18:02:45 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char		**init_fill_tab(char **tabhash, char *path, int res)
{
	struct dirent	*ent;
	DIR				*dir;
	char			*tmp;

	if ((dir = opendir(path)) == NULL)
		return (0);
	while ((ent = readdir(dir)))
	{
		if (ft_strcmp(ent->d_name, ".") && ft_strcmp(ent->d_name, ".."))
		{
			tmp = ft_str2join(path, "/", ent->d_name);
			if (!access(tmp, F_OK | X_OK) || !access(tmp, F_OK | W_OK))
			{
				if (tabhash[(res = hash_bin(ent->d_name))] != NULL)
					set_open_adressing(tabhash, res, tmp);
				else
					tabhash[res] = tmp;
			}
			else
				ft_strdel(&tmp);
		}
	}
	closedir(dir);
	return (tabhash);
}

void		hash_refresh(t_data *data)
{
	int		i;
	char	**env;

	env = data->env;
	i = 0;
	while (env && env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env || !env[i] || ft_strcmp(data->binpath, env[i] + 5))
	{
		if (ft_strcmp(get_user_name(data->env), "Unknown@") != 0)
		{
			if (data->binpath)
				ft_memdel((void **)&data->binpath);
		}
		get_tabhash(NULL, 1);
		init_hashtab(data, env, -1);
	}
}

char		*get_openaddr(char **tabhash, int hash, char *bin)
{
	char	*tmp;
	int		i;
	int		l;

	i = 0;
	l = 0;
	while (1)
	{
		if ((tmp = ft_chrbin(tabhash[hash])))
			if (tmp == NULL || !ft_strcmp(tmp, bin))
				break ;
		if (tmp == NULL || l == 2)
			return (NULL);
		hash++;
		if (hash > 2048 && l && (++l))
			hash = 0;
		else if (hash > 2048 && (++l))
			hash /= 7 + (++i);
	}
	return (tabhash[hash]);
}

char		*get_bin(char *bin)
{
	int		hash;
	char	**tabhash;

	hash = 0;
	if (!(tabhash = get_tabhash(NULL, 0)))
		return (NULL);
	hash = hash_bin(bin);
	if (hash > 2048 || !tabhash[hash])
		return (NULL);
	return (get_openaddr(tabhash, hash, bin));
}
