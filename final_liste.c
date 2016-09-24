/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 18:50:23 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/22 19:51:04 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		check_nd_stock_fd(char *str, t_lfd *fd, t_lfd *b)
{
	int nb;

	nb = ft_atoi(str);
	while (fd)
	{
		if (nb == fd->fd)
			nb = -1;
		if (!fd->next)
			break ;
		fd = fd->next;
	}
	if (nb != -1)
	{
		fd->next = (t_lfd *)malloc(sizeof(t_lfd));
		fd->next->next = NULL;
		fd->next->fd = nb;
		fd->next->open = 0;
		fd->next->read = 0;
		fd->next->write = 0;
	}
	fd = b;
}

int			find_redi_nb_aggr(char *str, t_lfd *fd, t_lfd *b, int nb)
{
	if (*(str + nb + 2) && ft_isdigit(*(str + nb + 2)))
	{
		nb = ft_atoi(str + nb + 2);
		while (fd)
		{
			if (nb == fd->fd)
				nb = -1;
			if (!fd->next)
				break ;
			fd = fd->next;
		}
		if (nb != -1)
		{
			fd->next = (t_lfd *)malloc(sizeof(t_lfd));
			fd->next->next = NULL;
			fd->next->fd = nb;
			fd->next->open = 0;
			fd->next->read = 0;
			fd->next->write = 0;
		}
		fd = b;
	}
	return (5);
}

int			choose_redi(char *str, t_lfd *fd, t_lfd *b)
{
	int i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (i)
		check_nd_stock_fd(str, fd, b);
	if (*(str + i) == '>' && !*(str + i + 1))
		return (1);
	else if (*(str + i) == '>' && *(str + i + 1) == '>')
		return (2);
	else if (*(str + i) == '>' && *(str + i + 1) == '&')
		return (find_redi_nb_aggr(str, fd, b, i));
	else if (*(str + i) == '<' && !*(str + i + 1))
		return (3);
	else if (*(str + i) == '<' && *(str + i + 1) == '<')
		return (4);
	return (0);
}

t_lredi		*get_redir(t_tk **tk, t_lredi *redi, t_lfd *fd)
{
	t_tk	*t;
	t_lredi	*b;

	t = *tk;
	redi = (t_lredi *)malloc(sizeof(t_lredi));
	b = redi;
	while (t && !(!t->tk && t->arg[0] == '|' && !t->arg[1]))
	{
		redi->str = ft_strdup(t->arg);
		if (t->tk)
			redi->redi = 0;
		else
			redi->redi = choose_redi(t->arg, fd, fd);
		t = t->next;
		if (!(t && !(!t->tk && t->arg[0] == '|' && !t->arg[1])))
			break ;
		redi->next = (t_lredi *)malloc(sizeof(t_lredi));
		redi = redi->next;
	}
	*tk = t;
	redi->next = NULL;
	return (b);
}

t_liste2	*final_list(t_liste2 *dest, t_tk *tk, int nb_pipe)
{
	t_liste2	*base;

	base = dest;
	while (nb_pipe--)
	{
		dest->fd = init_fd(NULL, NULL);
		dest->tabb = get_arg(&tk, NULL);
		if (tk && !(!tk->tk && tk->arg[0] == '|' && !tk->arg[1]))
			dest->redir = get_redir(&tk, NULL, dest->fd);
		else
			dest->redir = NULL;
		if (tk)
			tk = tk->next;
		if (nb_pipe)
		{
			dest->next = (t_liste2 *)malloc(sizeof(t_liste2));
			dest = dest->next;
			dest->next = NULL;
		}
	}
	dest->next = NULL;
	return (base);
}
