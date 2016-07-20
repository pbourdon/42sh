/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseandexc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 18:30:52 by hlouar            #+#    #+#             */
/*   Updated: 2016/05/23 09:30:42 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		checkaccess(char *str)
{
	if (access(str, F_OK) == 0)
		return (1);
	return (0);
}

char	*createbinpathtools(t_data *data, char *str, int i)
{
	free(str);
	str = ft_strjoin(data->allp[i], "/");
	str = ft_joinfree(str, data->args[0], 1);
	return (str);
}

int		createbinpath(t_data *data)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	changepathintab(data);
	if (data->allp)
	{
		if (createbinpath2(data, str) == 1)
			return (1);
		while (data->allp[i] != NULL)
		{
			str = createbinpathtools(data, str, i);
			if (access(str, F_OK) == 0)
			{
				data->bin = ft_strdup(str);
				freedata(str, data);
				return (1);
			}
			i++;
		}
	}
	errorbinary(data, str);
	return (0);
}

int		createthetab(t_data *data)
{
	int	i;
	int	o;

	o = 0;
	if (createbinpath(data) == 1)
	{
		data->tab = (char **)malloc(sizeof(char *) *
				ft_strlentab(data->args) + 1);
		data->tab[o++] = ft_strdup(data->bin);
		i = 1;
		while (data->args[i] != NULL)
		{
			data->tab[o] = ft_strdup(data->args[i]);
			o++;
			i++;
		}
		data->tab[o] = NULL;
		free(data->bin);
		return (1);
	}
	else
		return (-1);
}

void	forkall(t_data *data)
{
	pid_t	father;

	if (createthetab(data) == 1)
	{
		father = fork();
		if (father > 0)
			wait(0);
		else if (father == 0)
		{
			if (access(data->tab[0], F_OK) == 0)
			{
				if (data->envi == 1)
					execve(data->tab[0], data->tab, NULL);
				else
				{
					execve(data->tab[0], data->tab, data->env);
				}
			}
		}
		freetab(data->tab);
		return ;
	}
	else
		return ;
}
