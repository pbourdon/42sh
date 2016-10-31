/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 11:46:45 by bde-maze          #+#    #+#             */
/*   Updated: 2016/10/20 18:09:47 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char			**get_new_env(char **env)
{
	int		i;
	char	**new;

	i = -1;
	new = (char **)malloc(sizeof(char *) * (ft_strlentab(env) + 1));
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
			new[i] = ft_joinfree("SHLVL=", ft_itoa(ft_atoi(env[i] + 6) + 1), 2);
		else if (!ft_strncmp(env[i], "SHELL=", 6))
			new[i] = ft_joinfree("SHELL=", ft_joinfree(\
			ft_joinfree(getpwd(), "/", 1), "21sh", 1), 2);
		else
			new[i] = ft_strdup(env[i]);
	}
	new[i] = NULL;
	return (new);
}

t_builtin		*init_built(void)
{
	t_builtin	*built;

	built = (t_builtin *)malloc(sizeof(t_builtin) * 12);
	built[0].str = "cd";
	built[1].str = "env";
	built[2].str = "setenv";
	built[3].str = "unsetenv";
	built[4].str = "history";
	built[5].str = "export";
	built[6].str = "read";
	built[0].blt = cdcall;
	built[1].blt = callallenv;
	built[2].blt = callsetenv;
	built[3].blt = callunsetenv;
	built[4].blt = history;
	built[5].blt = insertthetmp;
	built[6].blt = ft_read;
	return (built);
}

t_data			*init_data(char **env, t_data *data)
{
	data->okchev = 0;
	data->exit = 0;
	data->args = NULL;
	data->exit_line = NULL;
	data->path = NULL;
	data->allp = NULL;
	data->voldpwd = NULL;
	data->pwd = NULL;
	data->cur_env = NULL;
	if (!env || !env[0])
	{
		data->env = (char **)malloc(sizeof(char *) * 4);
		data->env[0] = ft_strdup("TERM=xterm-256color");
		data->env[1] = ft_joinfree("PWD=", getpwd(), 2);
		data->env[2] = ft_strdup("SHLVL=1");
		data->env[3] = NULL;
	}
	else
		data->env = get_new_env(env);
	data->built = init_built();
	data->envi = 0;
	data->turn = 0;
	return (data);
}

int				main_init(t_term *term)
{
	if (term_init(term) == -1)
	{
		ft_putendl_fd("Error on init", 2);
		return (-1);
	}
	shell_init();
	g_shell.shell_heredoc = 0;
	return (0);
}

int				main(int ac, char **av, char **env)
{
	t_data		*data;
	t_term		first;

	(void)av;
	(void)ac;
	data = (t_data *)malloc(sizeof(t_data));
	data = init_data(env, data);
	init_hashtab(data, data->env, -1);
	main_init(&first);
	shell_loop(&first, data, env);
	return (0);
}
