/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <hlouar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 17:45:20 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/23 18:44:35 by cmichaud         ###   ########.fr       */
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
	if (data->dspam == 0)
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

void			print_list(t_liste *data)
{
	while (data)
	{
		printf("arg: %s\n", data->arg);
		data = data->next;
	}
}

void			sub_read(t_tree *tree, t_data *data)
{
	t_liste		*liste;
	t_liste		*tmp;

	liste = create_list();
	arg_to_list(liste, tree);
	liste = del_last_null_arg(liste);
	free_tree(tree);
	tmp = liste;
	while (tmp->next)
		tmp = tmp->next;
	tmp = liste;
	// print_list(tmp);
	while (tmp)
	{
		readgnl2(data, tmp->arg, liste);
		tmp = tmp->next;
	}
	free_list(liste);
}

int				readgnl(t_data *data, char *str)
{
	t_tk		*ptr;
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
			sub_read(tree, data);
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
	init_hashtab(env);
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
