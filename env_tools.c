/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 23:54:33 by cmichaud          #+#    #+#             */
/*   Updated: 2016/09/22 00:02:30 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		free_new_env(char **new)
{
	int i;

	i = -1;
	while (new[++i])
		ft_memdel((void **)&new[i]);
	free(new);
}

void		callenvitools(t_data *data, char **tabb, int i)
{
	if (data->fona == 1)
		freetab(tabb);
	else
		free(tabb);
	data->envi = 1;
	argsifenv(data, i);
	forkall(data, 0);
}

void		callenvi(t_data *data)
{
	int		i;
	char	**tabb;

	i = 2;
	tabb = (char **)malloc(sizeof(char *) * ft_strlentab(data->args) + 1);
	data->fona = 0;
	while (data->args[i])
	{
		if (ft_strstr(data->args[i], "=") != NULL)
		{
			tabb[i - 2] = ft_strdup(data->args[i]);
			data->fona = 1;
		}
		else
		{
			tabb[i - 2] = NULL;
			callenvitools(data, tabb, i);
			return ;
		}
		i++;
	}
	tabb[i - 2] = NULL;
	printab(tabb);
	freetab(tabb);
	data->envi = 0;
}

int			env_error(char **tabb)
{
	char	*tmp;
	int		i;

	i = 1;
	if (!ft_strcmp(tabb[i], "-i"))
		i++;
	while (tabb[i] && (tmp = ft_strchr(tabb[i], '=')))
	{
		if (tmp == tabb[i])
		{
			ft_putendl_fd("env : Invalid arguments", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void		p_or_e_choice(t_data *data, char **tabb, int i)
{
	tabb = newtab(tabb + i);
	free_new_env(data->liste->tabb);
	data->liste->tabb = tabb;
	if (!ft_strcmp(tabb[0], "env"))
		env_phase_2(data, 1);
	else
		exec_on_env(data);
	if (data->cur_env)
	{
		free_new_env(data->cur_env);
		data->cur_env = NULL;
	}
}
