/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/02 15:48:23 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/18 16:57:25 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		cd_on_pipe(t_data *data)
{
	char			**tabb;
	struct stat		sb;

	tabb = data->args;
	stat(tabb[1], &sb);
	if (!data->args[1])
		exit(0);
	if (data->args[1] && data->args[2] && data->args[3])
		ft_putendl_fd("cd: too many arguments", 2);
	else if (access(data->args[1], F_OK))
		ft_putendl_fd("cd: no such file or directory", 2);
	else if (access(tabb[1], F_OK | R_OK))
		ft_putendl_fd("cd: access denied", 2);
	else if ((S_ISREG(sb.st_mode)))
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putendl_fd(tabb[1], 2);
	}
	else
		exit(0);
	exit(255);
}

void		env_on_pipe(t_data *data)
{
	int i;

	i = -1;
	data->liste->tabb = newtab(data->args);
	while (data->args[++i])
		ft_memdel((void **)&data->args[i]);
	ft_memdel((void **)&data->args);
	callallenv(data);
	exit((data->binreturn = 0));
}

int			sub_exec_norm(t_data *data)
{
	if (!ft_strcmp(data->args[0], "exit"))
		exit_on_pipe(data, data->args);
	else if (!ft_strcmp(data->args[0], "export"))
		export_on_pipe(data);
	else if (!ft_strcmp(data->args[0], "cd"))
		cd_on_pipe(data);
	else if (ft_strcmp(data->args[0], "env") == 0)
		env_on_pipe(data);
	else if (ft_strcmp(data->args[0], "unset") == 0)
		exit(0);
	else if (ft_strcmp(data->args[0], "echo") == 0)
	{
		callecho(data->args);
		exit((data->binreturn = 0));
	}
	else
		return (0);
	return (1);
}

int			sub_exec(t_data *data)
{
	if ((ft_strlentab(data->args) == 1) &&\
				(ft_strcmp(data->args[0], "$?") == 0))
	{
		ft_putnbr(data->binreturn);
		ft_putchar('\n');
		exit((data->binreturn = 0));
	}
	else if (data->args && data->args[0] && !data->args[1] &&
		data->args[0][0] != '=' && ft_strchr(data->args[0], '='))
		exit(0);
	else if (!ft_strcmp(data->args[0], "history"))
		history(data);
	else if (!sub_exec_norm(data) && !is_a_builtin(data->args[0]))
		return (1);
	return (0);
}

int			execveremix(t_data *data)
{
	if (sub_exec(data) && createthetab(data) == 1)
	{
		if (access(data->tabb[0], F_OK) == 0)
		{
			ft_reset_term();
			if (data->envi == 1)
				execve(data->tabb[0], data->tabb, NULL);
			else
			{
				execve(data->tabb[0], data->tabb, data->env);
				return (1);
			}
		}
		freetab(data->tabb);
		freetab(data->args);
		return (-2);
	}
	exit(255);
}
