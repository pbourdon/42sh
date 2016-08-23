/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseandexc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:18:02 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/23 17:28:20 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	catchpath(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
	{
		if (ft_strstr(data->env[i], "PATH=") != NULL)
		{
			data->path = ft_strsub(data->env[i], 5, ft_strlen(data->env[i]));
			return ;
		}
		i++;
	}
}

void	changepathintab(t_data *data)
{
	catchpath(data);
	if (data->path)
	{
		data->allp = ft_strsplit(data->path, ':');
		free(data->path);
	}
}

int		createbinpath2(t_data *data, char *str)
{
	(void)str;
	if (!access(data->args[0], F_OK | X_OK) || !access(data->args[0], F_OK | W_OK))
	{
		data->bin = ft_strdup(data->args[0]);
		return (1);
	}
	return (0);
}

void	freedata(char *str, t_data *data)
{
	free(str);
	freetab(data->allp);
}
