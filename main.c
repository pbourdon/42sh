/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 17:45:20 by hlouar            #+#    #+#             */
/*   Updated: 2016/05/23 10:09:22 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	parsecommand(t_data *data)
{
	if (data->line[0] == '\0')
	{
		data->dspam = 1;
		return ;
	}
	data->args = ft_strsplit(data->line, ' ');
	if (ft_strcmp(data->line, "exit") == 0)
		exit(0);
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

void	readgnl2(t_data *data, char *str)
{
	data->fona = 0;
	data->dspam = 0;
	data->oldpwd = getpwd();
	gethome(data);
	str = (transformtab(withoutspace(str)));
	data->line = ft_strdup(str);
	free(str);
	parsecommand(data);
}

int		readgnl(t_data *data)
{
	t_token		*ptr;
	int			fd;
	char		*str;

	fd = 1;
	while (42)
	{
		writeonwhile();
		if (get_next_line(fd, &str) == 1)
		{
			ptr = to_list(str);
			readgnl2(data, str);
			if (data->dspam == 0)
				freetab(data->args);
			free(data->line);
			if (data->home)
				free(data->home);
			if (data->oldpwd)
				free(data->oldpwd);
		}
		else if (EOF)
		{
			ft_putendl("exit");
			return (0);
		}
	}
	return (0);
}

int		main(int ac, char **av, char **env)
{
	t_data	data;
	int		fd;

	fd = 0;
	data.path = NULL;
	(void)av;
	(void)ac;
	data.allp = NULL;
	data.voldpwd = NULL;
	data.env = env;
	if (data.env[0] == NULL)
	{
		data.env[0] = "PATH=/bin";
		data.env[1] = NULL;
	}
	data.envi = 0;
	data.turn = 0;
	readgnl(&data);
	return (0);
}
