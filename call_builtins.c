/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/29 00:40:21 by cmichaud          #+#    #+#             */
/*   Updated: 2016/08/29 00:55:55 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void			call_builtins(t_data *data)
{
	if (ft_strcmp(data->args[0], "export") == 0)
	{
		insertthetmp(data);
		return ;
	}
	else if (ft_strcmp(data->args[0], "env") == 0)
	{
		callallenv(data);
		return ;
	}
	else if (ft_strcmp(data->args[0], "setenv") == 0)
		callsetenv(data);
	else if (ft_strcmp(data->args[0], "unsetenv") == 0)
		callunsetenv(data);
	else if (ft_strcmp(data->args[0], "cd") == 0)
	{
//		ft_putstr("prout");
		cdcall(data);
	}
	else if (ft_strcmp(data->args[0], "history") == 0)
		history(data);
	else if (ft_strcmp(data->args[0], "exit") == 0)
		data->exit_lock = 1;
	else
		return ;
	exit(0);
}
