/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 17:13:01 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/22 10:30:40 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		is_a_builtin(char *str)
{
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "env") ||
		!ft_strcmp(str, "setenv") || !ft_strcmp(str, "unsetenv") ||
		!ft_strcmp(str, "echo") || !ft_strcmp(str, "exit") ||
		!ft_strcmp(str, "export") || !ft_strcmp(str, "unset") ||
		!ft_strcmp(str, "history") || !ft_strcmp(str, "read"))
		return (1);
	return (0);
}

int		builtin_check1(t_data *data)
{
	if ((ft_strlentab(data->args) == 1) &&\
		(ft_strcmp(data->args[0], "$?") == 0))
	{
		ft_putnbr(data->binreturn);
		ft_putchar('\n');
		data->binreturn = 0;
		return (1);
	}
	return (0);
}

int		builtin_check0(t_data *data)
{
	int i;

	i = -1;
	while (++i < 7)
		if (!ft_strcmp(data->built[i].str, data->liste->tabb[0]))
		{
			if (data->args)
				free_new_env(data->args);
			data->args = newtab(data->liste->tabb);
			data->built[i].blt(data);
			if (data->args)
				free_new_env(data->args);
			data->args = NULL;
			return (1);
		}
	return (0);
}

void	unset_norm(t_data *data)
{
	if (data->args)
		free_new_env(data->args);
	data->args = newtab(data->liste->tabb);
	deletefromenv(data, 1, 0);
	free_new_env(data->args);
	data->args = NULL;
}

void	builtin_no_pipe(t_data *data)
{
	int fd0;
	int fd1;
	int fd2;

	fd0 = dup(0);
	fd1 = dup(1);
	fd2 = dup(2);
	redi_loop(data->liste, data->liste->redir, data);
	ft_reset_term();
	if (builtin_check0(data))
		;
	else if (!ft_strcmp(data->liste->tabb[0], "exit"))
		exit_no_pipe(data, data->liste->tabb);
	else if (!ft_strcmp(data->liste->tabb[0], "echo"))
		callecho(data->liste->tabb);
	else if (!ft_strcmp(data->liste->tabb[0], "unset"))
		unset_norm(data);
	else
		builtin_check1(data);
	go_home();
	dup2(fd0, 0);
	dup2(fd2, 2);
	dup2(fd1, 1);
}
