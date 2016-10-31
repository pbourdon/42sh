/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 15:14:01 by bde-maze          #+#    #+#             */
/*   Updated: 2016/10/07 18:07:32 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		set_bin(char *path)
{
	char	**tabhash;
	int		hash;
	char	*bin;

	if (!access(path, F_OK | X_OK) || !access(path, F_OK | W_OK))
	{
		bin = ft_chrbin(path);
		hash = hash_bin(bin);
		tabhash = get_tabhash(NULL, 0);
		if (tabhash[hash] != NULL)
			set_open_adressing(tabhash, hash, path);
	}
}

int			is_there_a_path(char **env)
{
	int i;

	i = 0;
	while (env[i + 1])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}
