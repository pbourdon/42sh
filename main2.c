/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 18:50:23 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/26 07:00:44 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void			sub_parsecommand(t_data *data)
{
	if (ifitsredi(data) != 0)
	{
		mainredi(data);
		free(data->liste);
		freetab(data->oldtbe);
		return ;
	}
	else if (checklineok(data, data->args) != -1)
		return ;
	else if (ft_strcmp(data->args[0], "export") == 0)
		insertthetmp(data);
	else if (ft_strcmp(data->args[0], "env") == 0)
		callallenv(data);
	else if (ft_strcmp(data->args[0], "setenv") == 0)
		callsetenv(data);
	else if (ft_strcmp(data->args[0], "unsetenv") == 0)
		callunsetenv(data);
	else if (ft_strcmp(data->args[0], "cd") == 0)
		cdcall(data);
	else if (ft_strcmp(data->args[0], "history") == 0)
		history(data);
	else
		forkall(data);
}

void			parsecommand(t_data *data, t_liste *liste)
{
	if (data->line[0] == '\0')
	{
		data->dspam = 1;
		return ;
	}
	if (!(data->args = split_on_inib(data->line)))
		return ;
	if (ft_strcmp(data->line, "exit") == 0)
	{
		get_tabhash(NULL, 1);
		if (data->home)
			free(data->home);
		if (data->oldpwd)
			free(data->oldpwd);
		free(data->line);
		freetab(data->args);
		free_list(liste);
		exit(0);
	}
	sub_parsecommand(data);
}

int				switch_case(t_tk *ptr, int nb_redir, int nb_redir2)
{
	if (ptr->tk == 3 && ft_strncmp(ptr->arg, "|", 1) != 0 && ptr->next == NULL)
	{
		ft_putendl("Missing name for redirect.");
		return (-1);
	}
	else if (nb_redir > 1 || nb_redir2 < -1)
	{
		ft_putendl("Ambigous output redirect.");
		return (-1);
	}
	else if (ptr->tk == 3 && ft_strncmp(ptr->arg, "|", 1) == 0
	&& ptr->next == NULL)
	{
		ft_putendl("Invalid null command.");
		return (-1);
	}
	return (0);
}
