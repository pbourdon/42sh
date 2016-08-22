/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 18:50:23 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/22 18:50:37 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void			parsecommand(t_data *data)
{
	if (data->line[0] == '\0')
	{
		data->dspam = 1;
		return ;
	}
	data->args = ft_strsplit(data->line, ' ');
	if (ft_strcmp(data->line, "exit") == 0)
		exit(0);
	else if (ifitsredi(data) != 0)
	{
		mainredi(data);
		free(data->liste);
		freetab(data->oldtbe);
		return ;
	}
	else if (ft_strcmp(data->args[0], "env") == 0)
		callallenv(data);
	else if (ft_strcmp(data->args[0], "setenv") == 0)
		callsetenv(data);
	else if (ft_strcmp(data->args[0], "unsetenv") == 0)
		callunsetenv(data);
	else if (ft_strcmp(data->args[0], "cd") == 0)
		cdcall(data);
	else
		forkall(data);
}
