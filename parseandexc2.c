/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseandexc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:18:02 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/19 16:32:02 by cmichaud         ###   ########.fr       */
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
	str = ft_strdup(data->args[0]);
	// ft_putstr("TEST OF BINPATH2 = ");
	// ft_putnbr(access(str, F_OK));
	// ft_putendl(str);
	if (access(str, F_OK) == 0) // si le fichier existe bug de l executable
	{
		data->bin = ft_strdup(str);
		freedata(str, data);
		return (1);
	}
	free(str);
	return (0);
}

void	freedata(char *str, t_data *data)
{
	free(str);
	freetab(data->allp);
}
