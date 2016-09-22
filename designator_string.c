/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   designator_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 16:06:15 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/06 16:06:31 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		send_error(t_data *data)
{
	ft_putstr_fd("sh: ", 2);
	ft_putstr_fd(data->args[0], 2);
	ft_putendl_fd(": event not found", 2);
	data->binreturn = 255;
}

int			sub_loop(char **command, char *target)
{
	int		i;

	i = 0;
	while (command[i])
	{
		if (ft_strstr(command[i], target) != NULL)
			return (1);
		i++;
	}
	return (-1);
}

void		sub_design_to_string(t_data *data, char *command)
{
	ft_putendl(command);
	readgnl(data, create_command(command, data->args), 1);
}

void		design_to_string(t_data *data, char *target, int find)
{
	t_history	*history;
	char		**command;

	target += 2;
	history = g_shell.history;
	while (history)
	{
		command = ft_strsplit(history->str, ' ');
		if (sub_loop(command, target) == 1)
		{
			find = 1;
			break ;
		}
		history = history->next;
		freetab(command);
	}
	if (find == 1)
	{
		sub_design_to_string(data, history->str);
		return ;
	}
	else
		send_error(data);
}

void		design_to_start_string(t_data *data, char *target, int find)
{
	t_history	*history;
	char		**command;

	target++;
	history = g_shell.history;
	while (history)
	{
		command = ft_strsplit(history->str, ' ');
		if (ft_strstr(command[0], target) != NULL)
		{
			find = 1;
			break ;
		}
		history = history->next;
		freetab(command);
	}
	if (find == 1)
	{
		sub_design_to_string(data, history->str);
		return ;
	}
	else
		send_error(data);
}
