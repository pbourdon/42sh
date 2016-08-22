/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <hlouar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 17:45:20 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/19 12:13:28 by cmichaud         ###   ########.fr       */
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

void			readgnl2(t_data *data, char *str)
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

void			main_init(t_term *term)
{
	term_init(term);
	shell_init();
}

int				readgnl(t_data *data, char *str)
{
	t_tk		*ptr;
	t_liste		*liste;
	t_liste		*tmp;
	t_tree		*tree;
	int			fd;
	int			ret;

	fd = 1;
	ret = 0;
	if ((ptr = to_list(str, -1)))
	{
		ret = check_list(ptr, NULL, 0, 0);
		ptr = good_order(ptr, ptr, ptr);
		tree = to_tree(NULL, ptr, 5, NULL);
		free_first_list(ptr);
		if (ret == 0)
		{
			liste = create_list();
			arg_to_list(liste, tree);
			liste = del_last_null_arg(liste);
			free_tree(tree);
			tmp = liste;
			while (tmp->next)
				tmp = tmp->next;
			tmp = liste;
			while (tmp)
			{
				readgnl2(data, tmp->arg);
				tmp = tmp->next;
			}
			if (data->dspam == 0)
				freetab(data->args);
			free(data->line);
			if (data->home)
				free(data->home);
			if (data->oldpwd)
				free(data->oldpwd);
			free_list(liste);
		}
	}
	return (0);
}

int				main(int ac, char **av, char **env)
{
	t_data		data;
	t_term		first;
	int			fd;

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
	main_init(&first);
	shell_loop(&first, &data, env);
	return (0);
}
