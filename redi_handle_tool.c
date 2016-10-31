/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_handle_tool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 17:13:07 by cmichaud          #+#    #+#             */
/*   Updated: 2016/09/22 17:13:07 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		check_if_its_agreg(char *str)
{
	int i;
	int o;

	o = ft_strlen(str);
	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '>')
				break ;
			i++;
		}
		if (i == o)
			return (-1);
		if (str[i + 1] == '&')
			return (1);
	}
	return (0);
}

void	stock_fd(t_lfd *l, int fd, int t)
{
	while (l->next)
	{
		if (fd == l->fd)
			break ;
		l = l->next;
	}
	if (fd != l->fd)
	{
		l->next = (t_lfd *)malloc(sizeof(t_lfd));
		l = l->next;
	}
	l->fd = fd;
	l->open = 1;
	if (t)
	{
		l->write = 1;
		l->read = 0;
	}
	else
	{
		l->read = 1;
		l->write = 0;
	}
	l->next = NULL;
}

void	search_close_fd(t_liste2 *l, int df)
{
	t_lfd *fd;

	fd = l->fd;
	while (fd)
	{
		if (fd->fd == df)
		{
			close(df);
			fd->open = 0;
			fd->read = 0;
			fd->write = 0;
		}
		fd = fd->next;
	}
}
