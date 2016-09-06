/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 11:46:45 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/31 11:46:45 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			readgnl2(t_data *data, char *str, t_liste *liste)
{
	data->fona = 0;
	data->dspam = 0;
	data->oldpwd = getpwd();
	gethome(data);
	str = (transformtab(withoutspace(str)));
	data->line = ft_strdup(str);
	ft_strdel(&str);
	parsecommand(data, liste);
	if (data->dspam == 0 && data->args)
		ft_tabdel(&data->args);
	if (data->line != NULL)
		ft_strdel(&data->line);
	if (data->home)
		ft_strdel(&data->home);
	if (data->oldpwd)
		ft_strdel(&data->oldpwd);
}

void			main_init(t_term *term)
{
	term_init(term);
	shell_init();
}


int				opbi(char *operator, t_data *data)
{
	if (ft_strcmp(operator, "&&") == 0)
	{
		if (data->binreturn == 0)
			return (0);
		else
			return (-1);
	}
	if (ft_strcmp(operator, "||") == 0)
	{
		if (data->binreturn != 0)
			return (0);
		else
			return (-1);
	}
	return (0);
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
		ft_strdel(&data->line);
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
		{
			if (ft_strcmp(tmp->arg, ";"))
			{
				if (opbi(tmp->arg, data))
				{
					while (tmp->next && ft_strcmp(tmp->arg, ";"))
					{
						ft_strdel(&tmp->arg);
						tmp = tmp->next;
					}
				}
			}
			ft_strdel(&tmp->arg);
		}
		tmp = tmp->next;
	}
	free_list(liste);
}

void			printt(t_tk *ptr)
{
	while (ptr)
	{
		ft_putstr("token: ");
		ft_putnbr(ptr->tk);
		ft_putstr(" arg: ");
		ft_putendl(ptr->arg);
		ptr = ptr->next;
	}
}

int				readgnl(t_data *data, char *str, int fd)
{
	t_tk		*ptr;
	t_tree		*tree;
	int			ret;

	ret = 0;
	if ((ptr = to_list(str, -1)))
	{
		printt(ptr);
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

	data.okchev = 0;
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
