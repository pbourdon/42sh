/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 13:09:22 by bde-maze          #+#    #+#             */
/*   Updated: 2016/07/10 13:09:24 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/sh.h"

t_liste		*create_list()
{
	t_liste	*new;

	new = ft_memalloc(sizeof(t_liste));
	if (new != NULL)
	{
		new->head = NULL;
		new->tail = NULL;
	}
	return (new);
}

t_liste		*fill_list_tail(t_liste *liste, char *data)
{
	if (liste != NULL)
	{
		t_node *new = ft_memalloc(sizeof(t_liste));
		if (new != NULL)
		{
			new->str = data;
			new->next = NULL;
			if (liste->tail == NULL)
			{
				new->prev = NULL;
				liste->head = new;
				liste->tail = new;
			}
			else
			{
				liste->tail->next = new;
				new->prev = liste->tail;
				liste->tail = new;
			}
		}
	}
	return (liste);
}

t_liste		*fill_list_head(t_liste *liste, char *data)
{
	if (liste != NULL)
	{
		t_node *new = ft_memalloc(sizeof(t_liste));
		if (new != NULL)
		{
			new->str = data;
			new->prev = NULL;
			if (liste->tail == NULL)
			{
				new->next = NULL;
				liste->head = new;
				liste->tail = new;
			}
			else
			{
				liste->head->prev = new;
				new->next = liste->head;
				liste->head = new;
			}
		}
	}
	return (liste);
}

void				print_list(t_liste *liste)
{
	while (liste != NULL)
	{
		ft_putstr(liste->head->str);
		liste->head = liste->head->next;
	}
}

int					main(int argc, char **argv)
{

	(void)argc;
	(void)argv;
	int				n = 512;
	t_liste			*liste;
	char			buffer[n];
	size_t			ret;

	liste = create_list();
	while (42)
	{
		ret = read(0, buffer, n);
		if (ret > 0)
		{
			liste = fill_list_tail(liste, buffer);
		}
		// print_list(liste);
		ft_putstr("buf: ");
		ft_putendl(buffer);
	}
	return(0);
}
