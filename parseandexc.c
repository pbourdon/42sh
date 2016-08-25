/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseandexc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <hlouar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 18:30:52 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/25 14:50:53 by pguzman          ###   ########.fr       */
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

int		createbinpath(t_data *data, int n)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	if (data->args && data->args[0] &&
		!ft_strncmp(data->args[0], "./", 2) &&
		createbinpath2(data, str) == 1)
		return (1);
	else if ((str = get_bin(data->args[0])))
	{
		data->bin = ft_strdup(str);
		return (1);
	}
/*		while (data->allp[i] != NULL)
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
		}*/
	if (n == 1)
		errorbinary(data, str);
	return (0);
}

int		createthetab(t_data *data)
{
	int	i;
	int	o;

	o = 0;
	if (createbinpath(data, 1) == 1)
	{
		data->tabb = (char **)malloc(sizeof(char *) *
				ft_strlentab(data->args) + 1);
		data->tabb[o++] = ft_strdup(data->bin);
		i = 1;
		while (data->args[i] != NULL)
		{
			data->tabb[o] = ft_strdup(data->args[i]);
			o++;
			i++;
		}
		data->tabb[o] = NULL;
		free(data->bin);
		return (1);
	}
	else
	{
		return (-1);
	}
}

void	forkall(t_data *data)
{
	pid_t	father;

	if (createthetab(data) == 1)
	{
		father = fork();
		if (father > 0)
		{
			wait(0);
			ft_reset_term(g_shell.term_reset.term);
		}
		else if (father == 0)
		{
			if (access(data->tabb[0], F_OK) == 0)
			{
				ft_reset_term(g_shell.term_reset.term_copy);
				if (data->envi == 1)
					execve(data->tabb[0], data->tabb, NULL);
				else
				{
					execve(data->tabb[0], data->tabb, data->env);
				}
			}
		}
		freetab(data->tabb);
		return ;
	}
	else
		return ;
}
