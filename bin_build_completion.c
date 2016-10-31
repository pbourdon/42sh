/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_build_completion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 11:15:35 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/21 12:00:49 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

t_liste		*get_list_bin_norm(char **tabb, t_liste *list, char *path, int i)
{
	int		slash;
	int		j;

	j = -1;
	slash = 0;
	while (++i < 4096)
	{
		if (tabb[i] && tabb[i][0])
		{
			j = -1;
			while (tabb[i][++j])
				if (tabb[i][j] == '/')
					slash = j;
			if (slash)
				slash++;
			if (!ft_strncmp(path, tabb[i] + slash, ft_strlen(path)))
				list = get_next(list, ft_strdup(tabb[i] + slash));
		}
	}
	free(path);
	return (list);
}

t_liste		*get_list_of_bin_completion(char *path)
{
	char	**tabb;
	int		i;
	t_liste *list;

	list = NULL;
	if (!path || !path[0])
	{
		free(path);
		return (NULL);
	}
	if (!ft_strncmp(path, "./", 2) || path[0] == '/')
		return (get_list_of_file_completion(path));
	tabb = get_tabhash(NULL, 0);
	i = -1;
	return (get_list_bin_norm(tabb, list, path, i));
}
