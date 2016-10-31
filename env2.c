/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:47:46 by bde-maze          #+#    #+#             */
/*   Updated: 2016/10/21 16:33:41 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	env_phase_2_2(t_data *data, int e)
{
	char **tmp;

	if (e)
	{
		tmp = data->cur_env;
		data->cur_env = get_env_nd_var(data->liste->tabb, tmp);
		free_new_env(tmp);
	}
	else
		data->cur_env = get_env_nd_var(data->liste->tabb, data->env);
}

void	env_phase_2(t_data *data, int e)
{
	if (!data->liste->tabb[1])
		return (printab(data->cur_env));
	else if (env_error(data->liste->tabb))
		data->binreturn = 1;
	else if (!ft_strcmp(data->liste->tabb[1], "-i"))
	{
		if (e)
			free_new_env(data->cur_env);
		data->cur_env = get_var(data->liste->tabb);
	}
	else
		env_phase_2_2(data, e);
	data->binreturn = 0;
	print_or_exec(data);
}

void	exec_on_env(t_data *data)
{
	pid_t	t;

	data->binreturn = 0;
	free_new_env(data->args);
	if ((t = fork()) == 0)
	{
		data->args = newtab(data->liste->tabb);
		if (is_a_builtin(data->args[0]))
		{
			builtin_no_pipe(data);
			free_new_env(data->args);
			exit(1);
		}
		if (createthetab(data))
		{
			free_new_env(data->args);
			execve(data->tabb[0], data->tabb, data->cur_env);
		}
		exit(1);
	}
	else
		waitpid(t, &data->binreturn, 0);
	data->args = NULL;
}

void	print_or_exec(t_data *data)
{
	char	*tmp;
	char	**tabb;
	int		i;
	int		p;

	p = -1;
	tabb = data->liste->tabb;
	i = 1;
	if (!ft_strcmp(tabb[i], "-i"))
		i++;
	while (tabb[i] && (tmp = ft_strchr(tabb[i], '=')))
		i++;
	if (!tabb[i])
	{
		printab(data->cur_env);
		free_new_env(data->cur_env);
		data->cur_env = NULL;
		return ;
	}
	else
		p_or_e_choice(data, tabb, i);
}

void	callallenv(t_data *data)
{
	if (!data->liste->tabb[1])
		return (printab(data->env));
	env_phase_2(data, 0);
}
