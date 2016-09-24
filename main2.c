/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 18:50:23 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/24 17:32:41 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int				search_nb_pipe(t_tk *tk)
{
	int nb;

	nb = 0;
	while (tk)
	{
		if (!tk->tk && !tk->arg[1] && tk->arg[0] == '|')
			++nb;
		tk = tk->next;
	}
	return (nb);
}

int				is_a_sepp(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		i++;
	}
	if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		return (1);
	return (0);
}

char			**get_arg(t_tk **tk, char **tabb)
{
	t_tk	*t;
	int		i;

	i = 0;
	t = *tk;
	while (t)
	{
		if ((++i) && !t->tk && is_a_sepp(t->arg))
			break ;
		t = t->next;
	}
	t = *tk;
	tabb = (char **)malloc(sizeof(char *) * (i + 1));
	tabb[i] = NULL;
	i = -1;
	while (t && !(!t->tk && is_a_sepp(t->arg)))
	{
		tabb[++i] = ft_strdup(t->arg);
		t = t->next;
	}
	tabb[++i] = NULL;
	*tk = t;
	return (tabb);
}

t_lfd			*init_fd(t_lfd *fd, t_lfd *base)
{
	fd = (t_lfd *)malloc(sizeof(t_lfd));
	base = fd;
	fd->fd = 0;
	fd->open = 1;
	fd->write = 1;
	fd->read = 0;
	fd->next = (t_lfd *)malloc(sizeof(t_lfd));
	fd = fd->next;
	fd->open = 1;
	fd->write = 0;
	fd->read = 1;
	fd->fd = 1;
	fd->next = (t_lfd *)malloc(sizeof(t_lfd));
	fd = fd->next;
	fd->fd = 2;
	fd->open = 1;
	fd->write = 1;
	fd->read = 0;
	fd->next = NULL;
	return (base);
}

void			built_or_launch(t_data *data)
{
	data->args = newtab(data->liste->tabb);
	if (!data->liste->next && (is_a_builtin(data->liste->tabb[0])\
		|| checklineok(data, data->liste->tabb) != -1\
		|| (ft_strlentab(data->args) == 1 &&\
			ft_strcmp(data->args[0], "$?") == 0)))
	{
		builtin_no_pipe(data);
		return (free_all(data, data->liste));
	}
	free_new_env(data->args);
	data->args = NULL;
	launch_main_fork(data);
}

void			parsecommand(t_data *data, t_liste *liste)
{
	int			i;
	int			nb_pipe;
	t_liste2	*dest;

	(void)liste;
	data->l = nsplit_on_inib(data->line);
	if ((nb_pipe = search_nb_pipe(data->l) + 1) > 512)
	{
		free_all(data, NULL);
		return (ft_putendl_fd("sh : over pipe limit", 2));
	}
	dest = (t_liste2 *)malloc(sizeof(t_liste2));
	data->liste = final_list(dest, data->l, nb_pipe);
    i = -1;
    while (data->args && data->args[++i])
        ft_memdel((void **)&data->args[i]);
	if (data->args)
		ft_memdel((void **)&data->args);
	data->args = newtab(data->liste->tabb);
 	if (!check_syntax_designator(data))
	{
		data->d = 0;
		return (designator(data, data->liste));
	}
    i = -1;
    while (data->args && data->args[++i])
        ft_memdel((void **)&data->args[i]);
	if (data->args)
		ft_memdel((void **)&data->args);
	built_or_launch(data);
}
