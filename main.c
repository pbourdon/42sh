/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 11:46:45 by cmichaud          #+#    #+#             */
/*   Updated: 2016/08/31 11:46:45 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <stdio.h>

void			readgnl2(t_data *data, char *str, t_liste *liste)
{
	data->fona = 0;
	data->dspam = 0;
	data->oldpwd = getpwd();
	gethome(data);
	str = (transformtab(withoutspace(str)));
	data->line = ft_strdup(str);
	free(str);
	parsecommand(data, liste);
	if (data->dspam == 0 && data->args)
		freetab(data->args);
	free(data->line);
	if (data->home)
		free(data->home);
	if (data->oldpwd)
		free(data->oldpwd);
}

void			main_init(t_term *term)
{
	term_init(term);
	shell_init();
}

void			sub_read(t_tree *tree, t_data *data)
{
	t_liste		*liste;
	t_liste		*tmp;

	liste = create_list();
	arg_to_list(liste, tree);
	liste = del_last_null_arg(liste);
	free_tree(tree);
	if (check_list_2(liste))
	{
		free_list2(liste);
		free(data->line);
		return ;
	}
	else
		tmp = liste;
	while (tmp)
	{
		if (ft_strcmp(tmp->arg, ";") && ft_strcmp(tmp->arg, "||") &&
			ft_strcmp(tmp->arg, "&&"))
			readgnl2(data, tmp->arg, liste);
		else
			free(tmp->arg);
		tmp = tmp->next;
	}
	free_list(liste);
}

int				readgnl(t_data *data, char *str, int fd)
{
	t_tk		*ptr;
	t_tree		*tree;
	int			ret;

	ret = 0;
	if ((ptr = to_list(str, -1)))
	{
		ret = check_list(ptr, ptr, 0, 0);
		ptr = good_order(ptr, ptr, ptr);
		tree = to_tree(NULL, ptr, 5, NULL);
		if (ret == 0)
			sub_read(tree, data);
		else
			free_tree(tree);
	}
	ret = 0;
	if (data->exit)
	{
		fd = ft_exit_error(data, &ret);
		data->exit = 0;
		if (ret == 1)
			exit(fd);
	}
	return (0);
}

int				main(int ac, char **av, char **env)
{
	t_data		data;
	t_term		first;
	int			fd;

	fd = 0;
	data.exit = 0;
	data.exit_line = NULL;
	data.path = NULL;
	(void)av;
	(void)ac;
	data.allp = NULL;
	data.voldpwd = NULL;
	data.env = env;
	init_hashtab(env, -1);
	if (data.env[0] == NULL)
	{
		data.env[0] = "PATH=/bin";
		data.env[1] = "TERM=xterm-256color";
		data.env[2] = NULL;
	}
	data.envi = 0;
	data.turn = 0;
	main_init(&first);
	shell_loop(&first, &data, env);
	return (0);
}
