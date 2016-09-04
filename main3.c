/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 12:25:20 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/31 12:25:31 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			sub_parsecommand2(t_data *data)
{
	if ((ft_strlentab(data->args) == 1) &&
		(ft_strcmp(data->args[0], "$?") == 0))
	  {
			ft_putnbr(data->binreturn);
			ft_putendl(": Command not found.");
			data->binreturn = 255;
	}
}

void			sub_sub_parse(t_data *data)
{
	mainredi(data, 0);
	free_liste2(data->liste);
	freetab(data->oldtbe);
	if (data->okchev == 1)
	{
		data->okchev = 0;
		freetab(data->tabchev);
	}
}

void			sub_parsecommand(t_data *data, int i)
{
	if (ifitsredi(data) != 0)
		return (sub_sub_parse(data));
	else if (checklineok(data, data->args) != -1)
		return ;
	else if (ft_strcmp(data->args[0], "export") == 0 && (i = 1))
		insertthetmp(data);
	else if (ft_strcmp(data->args[0], "env") == 0 && (i = 1))
		callallenv(data);
	else if (ft_strcmp(data->args[0], "setenv") == 0 && (i = 1))
		callsetenv(data);
	else if (ft_strcmp(data->args[0], "unsetenv") == 0 && (i = 1))
		callunsetenv(data);
	else if (ft_strcmp(data->args[0], "cd") == 0 && (i = 1))
		cdcall(data);
	sub_parsecommand2(data);
	if (ft_strcmp(data->args[0], "history") == 0 && (i = 1))
		history(data);
	else if (i == 0 && ft_strcmp(data->args[0], "exit") != 0)
		forkall(data, 0);
	return ;
}
