/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 16:29:37 by cmichaud          #+#    #+#             */
/*   Updated: 2016/09/22 23:43:21 by cmichaud         ###   ########.fr       */
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

t_liste			*sub_read_cond2(t_data *data, t_liste *tmp)
{
	if (ft_strcmp(tmp->arg, ";"))
		if (opbi(tmp->arg, data))
			while (tmp->next && ft_strcmp(tmp->arg, ";"))
			{
				ft_strdel(&tmp->arg);
				tmp = tmp->next;
			}
	ft_strdel(&tmp->arg);
	return (tmp);
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
	while (tmp)
	{
		if (ft_strcmp(tmp->arg, ";") && ft_strcmp(tmp->arg, "||") &&
			ft_strcmp(tmp->arg, "&&"))
			readgnl2(data, tmp->arg, liste);
		else
			tmp = sub_read_cond2(data, tmp);
		tmp = tmp->next;
	}
	free_list(liste);
}

int				readgnl(t_data *data, char *str)
{
	t_tk		*ptr;
	t_tree		*tree;
	int			ret;

	ret = 0;
	if ((ptr = to_list(str, -1)))
	{
		ret = check_list(ptr);
		ptr = good_order(ptr, ptr, ptr);
		tree = to_tree(NULL, ptr, 5, NULL);
		if (ret == 0)
			sub_read(tree, data);
		else
			free_tree(tree);
	}
	ret = 0;
	return (0);
}