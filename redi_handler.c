/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 17:07:20 by cmichaud          #+#    #+#             */
/*   Updated: 2016/09/22 17:35:13 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		to_to_handle_heredoc(t_liste2 *l, t_lredi *liste, t_data *data)
{
	t_lredi		*tmp;
	t_history	*hist;
	t_hist_cont	*hc;

	hist = NULL;
	tmp = liste;
	hist = data->hist_cont->hist;
	hc = data->hist_cont->next;
	ft_memdel((void **)&data->hist_cont);
	data->hist_cont = hc;
	while ((tmp = tmp->next))
		if (tmp->redi == 4)
			return (free_heredoc(hist));
	return (heredoc_to_stdin(l, hist, hist));
}

void		to_handle_agreg(t_liste2 *l, t_lredi *liste)
{
	t_lredi *tmp;

	tmp = liste;
	if (decoupe2(tmp->str)[0] == '-')
		search_close_fd(l, ft_atoi(decoupe1(tmp->str)));
	else if (ft_strchr(tmp->str, '>'))
		dup2(ft_atoi(decoupe2(tmp->str)), ft_atoi(decoupe1(tmp->str)));
}

void		to_main_fork_redirection(t_liste2 *l, t_lredi *liste)
{
	int		out;
	t_lredi *tmp;

	out = 1;
	tmp = liste;
	if ((out = open(tmp->next->str, O_WRONLY | O_TRUNC |
					O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR | O_APPEND |
					S_IRWXO)) == -1)
	{
		ft_putstr_fd(tmp->next->str, 2);
		ft_putendl_fd(": Open denied", 2);
		exit(1);
	}
	stock_fd(l->fd, out, 1);
	dup2(out, ft_atoi(tmp->str));
}

void		to_main_fork_redirection2(t_liste2 *l, t_lredi *liste)
{
	t_lredi *tmp;
	int		in;

	in = 0;
	tmp = liste;
	if ((in = open(tmp->next->str, O_RDONLY)) == -1)
	{
		ft_putstr_fd(tmp->next->str, 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(0);
	}
	stock_fd(l->fd, in, 0);
	dup2(in, ft_atoi(tmp->str));
}

void		to_main_fork_redirection_dbl(t_liste2 *l, t_lredi *liste)
{
	int		out;
	t_lredi *tmp;

	out = 1;
	tmp = liste;
	if ((out = open(tmp->next->str, O_RDWR | O_APPEND)) == -1)
		return (to_main_fork_redirection(l, tmp));
	stock_fd(l->fd, out, 1);
	dup2(out, ft_atoi(tmp->str));
}
