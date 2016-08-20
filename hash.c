/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 17:16:42 by cmichaud          #+#    #+#             */
/*   Updated: 2016/08/19 16:26:52 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_tabhash(void)
{
	int		i;
	char	**tabhash;

	tabhash = get_tabhash(NULL);
	if (tabhash == NULL)
		return ;
	i = -1;
	while (++i < 4096)
		if (tabhash[i])
			ft_memdel((void **)&tabhash[i]);
	ft_memdel((void **)tabhash);
}

char	*ft_chrbin(char *path)
{
	int i;

	i = ft_strlen(path);
	while (path[--i])
	{
		if (path[i] == '/')
		{
			i++;
			return (path + i);
		}
	}
	return (0);
}

int		hash_bin(char *bin)
{
	int i;
	int res;
	
	i = -1;
	res = 1;
	while (bin[++i])
		res = res + (bin[i] * 3);
	while (res >= 4096)
		res = (res >> 2);
	return (res);
}

void	set_open_adressing(char **tabhash, int res, char *path)
{
	int i;

	i = 0;
	while (tabhash[res] != NULL)
	{
		res++;
		if (res >= 4096)
			res /= 7 + (++i);
	}
	tabhash[res] = path;
}

char	*ft_str2join(char *bar, char *yoo, char *foo)
{
	char *tmp;
	char *t;

	tmp = ft_strjoin(bar, yoo);
	t = ft_strjoin(tmp, foo);
	free(tmp);
	return (t);
}

void	set_bin(char *path)
{
	char	**tabhash;
	int		hash;
	char	*bin;

	if (!access(path, F_OK | X_OK) || !access(path, F_OK | W_OK))
	{
		bin = ft_chrbin(path);
		hash = hash_bin(bin);
		tabhash = get_tabhash(NULL);
		if (tabhash[hash] != NULL)
			set_open_adressing(tabhash, hash, path);
	}
}

char	**init_fill_tab(char **tabhash, char *path)
{
	struct dirent	*ent;
	DIR				*dir;
	char			*tmp;
	int				res;
	int				i;

	res = 0;
	i = -1;
	if ((dir = opendir(path)) == NULL)
		return (0);
	while ((ent = readdir(dir)))
	{
		if (++i > 2)
		{
			tmp = ft_str2join(path, "/", ent->d_name);
			if (!access(tmp, F_OK | X_OK) || !access(tmp, F_OK | W_OK))
			{
				if (tabhash[(res = hash_bin(ent->d_name))] != NULL)
					set_open_adressing(tabhash, res, tmp);
				else
					tabhash[res] = tmp;
			}
		}
	}
	return (tabhash);
}

char	**ft_create_bin_path(void)
{
	char **path;
	char *tmp;

	tmp = "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/munki";
	path = ft_strsplit(tmp, ':');
	return (path);
}

void	init_hashtab(char **env)
{
	int			i;
	char		**path;
	char		**tabhash;

	i = 0;
	path = NULL;
	if (!(tabhash = (char **)malloc(sizeof(char *) * 4096)))
		return ;
	while (++i <= 4096)
		tabhash[i] = NULL;
	i = 0;
	while (env && env[0] && ft_strncmp(env[i], "PATH=", 5))
		++i;
	if (env[i])
		path = ft_strsplit((env[i] + 5), ':');
	else
		path = ft_create_bin_path();
	i = -1;
	while (path && path[++i])
	{
		if (!access(path[i], F_OK | X_OK) || !access(path[i], F_OK | W_OK))
			tabhash = init_fill_tab(tabhash, path[i]);
	}
	get_tabhash(tabhash);
}

char	*get_openaddr(char **tabhash, int hash, char *bin)
{
	char *tmp;

	while (1)
	{
		if ((tmp = ft_chrbin(tabhash[hash])))
			if (!ft_strcmp(tmp, bin))
				break ;
		hash++;
	}
	return (tabhash[hash]);
}

char	*get_bin(char *bin)
{
	int		hash;
	char	**tabhash;

	hash = 0;
	tabhash = get_tabhash(NULL);
	hash = hash_bin(bin);
	if (hash > 4096 || !tabhash[hash])
		return (NULL);
	return (get_openaddr(tabhash, hash, bin));
}

char	**get_tabhash(char **new)
{
	static char	**tabhash = NULL;

	if (tabhash == NULL && (tabhash = new))
		return (NULL);
	return (tabhash);
}

