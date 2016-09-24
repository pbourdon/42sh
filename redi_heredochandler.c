/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newredi11.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 23:06:44 by cmichaud          #+#    #+#             */
/*   Updated: 2016/09/22 17:08:41 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		free_heredoc(t_history *hist)
{
	t_history *t;

	while (hist)
	{
		t = hist->next;
		ft_memdel((void **)&hist->str);
		ft_memdel((void **)&hist);
		hist = t;
	}
	return ;
}

void		heredoc_to_stdin(t_liste2 *l, t_history *hist, t_history *t)
{
	int out;

	if ((out = open(".file_for_ready", O_RDWR | O_TRUNC |
					O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR | O_APPEND |
					S_IRWXO)) == -1)
	{
		ft_putendl_fd("heredoc failed", 2);
		exit(1);
	}
	while (hist->next)
	{
		ft_putendl_fd(hist->str, out);
		hist = hist->next;
	}
	close(out);
	if ((out = open(".file_for_ready", O_RDONLY)) == -1)
	{
		ft_putstr_fd("heredoc failed", 2);
		exit(1);
	}
	dup2(out, 0);
	stock_fd(l->fd, out, 0);
	return (free_heredoc(t));
}

void		stock_heredoc(t_data *data, char *str)
{
	t_hist_cont *t;

	if (!data->hist_cont)
	{
		data->hist_cont = (t_hist_cont *)malloc(sizeof(t_hist_cont));
		data->hist_cont->next = NULL;
		data->hist_cont->hist = double_left(str);
		return ;
	}
	t = data->hist_cont;
	while (t->next)
	{
		t = t->next;
	}
	t->next = (t_hist_cont *)malloc(sizeof(t_hist_cont));
	t->next->next = NULL;
	t->next->hist = double_left(str);
}

void		stock_all_heredoc(t_data *data, t_liste2 *l)
{
	t_lredi *r;

	while (l)
	{
		r = l->redir;
		while (r)
		{
			if (r->redi == 4)
			{
				stock_heredoc(data, r->next->str);
			}
			r = r->next;
		}
		l = l->next;
	}
}
