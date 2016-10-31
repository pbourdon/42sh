/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_build_completion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 10:14:50 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/21 11:16:23 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

t_liste		*stock_as_sort(t_liste *b, t_liste *l, t_liste *t, t_liste *n)
{
	if (t == l)
	{
		n->next = l;
		return (n);
	}
	n->next = l;
	t->next = n;
	return (b);
}

t_liste		*get_next(t_liste *list, char *str)
{
	t_liste *node;
	t_liste *tmp;
	t_liste *b;

	if (!(node = (t_liste *)malloc(sizeof(t_liste))))
		return (list);
	node->next = NULL;
	if (!ft_strncmp(str, "./", 2))
		node->arg = ft_strdup(str + 2);
	else
		node->arg = ft_strdup(str);
	free(str);
	if (!list)
		return (node);
	b = list;
	tmp = list;
	while (list)
	{
		if (ft_strcmp(list->arg, node->arg) > 0)
			break ;
		tmp = list;
		list = list->next;
	}
	return (stock_as_sort(b, list, tmp, node));
}

char		*get_sub_path_norm(char *path)
{
	int		i;
	int		swap;
	char	*str;
	char	*tmp;

	i = -1;
	swap = 0;
	while (path[++i])
		if (path[i] == '/')
			swap = i;
	if (!swap)
		return (ft_strdup("./"));
	path[swap] = 0;
	if (ft_strncmp(path, "./", 2))
		tmp = ft_strjoin("./", path);
	else
		tmp = ft_strdup(path);
	str = ft_strjoin(tmp, "/");
	ft_bzero(tmp, ft_strlen(tmp));
	ft_strcpy(tmp, path + swap + 1);
	path[swap] = '/';
	ft_bzero(path, ft_strlen(path));
	ft_strcpy(path, tmp);
	free(tmp);
	return (str);
}

char		*get_sub_path(char *path)
{
	int		i;
	int		swap;
	char	*str;
	char	*tmp;

	i = -1;
	swap = 0;
	if (path[0] == '/')
	{
		while (path[++i])
			if (path[i] == '/')
				swap = i;
		path[swap] = 0;
		str = ft_strjoin(path, "/");
		tmp = ft_strdup(path + swap + 1);
		ft_bzero(path, ft_strlen(path));
		ft_strcpy(path, tmp);
		free(tmp);
		return (str);
	}
	return (get_sub_path_norm(path));
}

t_liste		*get_list_of_file_completion(char *path)
{
	DIR				*fd_d;
	struct dirent	*dir;
	char			*open_path;
	int				len;
	t_liste			*list;

	open_path = get_sub_path(path);
	len = ft_strlen(path);
	if (!(fd_d = opendir(open_path)))
	{
		free(path);
		free(open_path);
		return (NULL);
	}
	list = NULL;
	while ((dir = readdir(fd_d)))
		if ((len == 0 && ft_strncmp(dir->d_name, ".", 1)) ||
			(len && !ft_strncmp(dir->d_name, path, len)))
			list = get_next(list, ft_strjoin(open_path, dir->d_name));
	closedir(fd_d);
	free(path);
	free(open_path);
	return (list);
}
