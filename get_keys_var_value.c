/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_keys_var_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 10:06:36 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/22 10:08:30 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char		*get_key_value(char *key, char **env)
{
	int		i;
	char	*mpt;

	i = -1;
	while (env && env[++i])
	{
		mpt = ft_strchr(env[i], '=');
		*mpt = 0;
		if (!ft_strcmp(env[i], key))
		{
			*mpt = '=';
			mpt = ft_strdup(mpt + 1);
			return (mpt);
		}
		*mpt = '=';
	}
	return (NULL);
}

char		*get_key_value2(char *key, char **env)
{
	int		i;
	char	*mpt;

	i = -1;
	while (env && env[++i])
	{
		if (!ft_strcmp(env[i], key))
		{
			if (env[i + 1] && env[i + 2])
			{
				mpt = ft_strdup(env[i + 2]);
				return (mpt);
			}
			else
				return (NULL);
		}
		if (env[i + 1] && env[i + 2])
			i += 2;
		else
			break ;
	}
	return (NULL);
}
