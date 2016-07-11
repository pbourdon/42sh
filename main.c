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

t_liste			*create_list()
{
	t_liste		*new;

	new = ft_memalloc(sizeof(t_liste));
	if (new != NULL)
	{
		new->data = ft_strdup("x");
		new->next = NULL;
		new->prev = NULL;		
	}
	return (new);
}


void			fill_list(t_liste *liste, char *str)
{
	t_liste		*new;

	new = ft_memalloc(sizeof(t_liste));
	if (new != NULL)
	{
		new->data = ft_strdup(str);
		while (ft_strcmp(liste->data, "x"))
			liste = liste->next;
		if (liste->prev == NULL)
		{
			liste->prev = new;
			new->prev = NULL;
			new->next = liste;
		}
		else
		{
			liste->prev->next = new;
			new->prev = liste->prev;
			liste->prev = new;
			new->next = liste;
		}
	}
}

// t_liste		*create_list()
// {
// 	t_liste	*new;

// 	new = ft_memalloc(sizeof(t_liste));
// 	if (new != NULL)
// 	{
// 		new->head = NULL;
// 		new->tail = NULL;
// 	}
// 	return (new);
// }

// t_liste		*fill_list_tail(t_liste *liste, char *data)
// {
// 	if (liste != NULL)
// 	{
// 		t_node *new = ft_memalloc(sizeof(t_liste));
// 		if (new != NULL)
// 		{
// 			new->str = data;
// 			new->next = NULL;
// 			if (liste->tail == NULL)
// 			{
// 				new->prev = NULL;
// 				liste->head = new;
// 				liste->tail = new;
// 			}
// 			else
// 			{
// 				liste->tail->next = new;
// 				new->prev = liste->tail;
// 				liste->tail = new;
// 			}
// 		}
// 	}
// 	return (liste);
// }

// t_liste		*fill_list_head(t_liste *liste, char *data)
// {
// 	if (liste != NULL)
// 	{
// 		t_node *new = ft_memalloc(sizeof(t_liste));
// 		if (new != NULL)
// 		{
// 			new->str = data;
// 			new->prev = NULL;
// 			if (liste->tail == NULL)
// 			{
// 				new->next = NULL;
// 				liste->head = new;
// 				liste->tail = new;
// 			}
// 			else
// 			{
// 				liste->head->prev = new;
// 				new->next = liste->head;
// 				liste->head = new;
// 			}
// 		}
// 	}
// 	return (liste);
// }

void				print_list(t_liste *liste)
{
	while (liste->prev != NULL)
	{
		liste = liste->prev;
	}

	while (liste != NULL)
	{
		ft_putstr(liste->data);
		liste = liste->next;
	}
}

int					main(int argc, char **argv)
{
	struct termios		term;

	(void)argc;
	(void)argv;
	t_liste			*liste;
	char			buffer[5];
	size_t			ret;

	// if ((tgetent(NULL, getenv("TERM"))) < 1)
		// return (-1);
	// if ((tcgetattr(0, &term)) == -1)
		// return (-1);
	// term.c_lflag &= ~(ICANON | ECHO);
	// term.c_cc[VMIN] = 1;
	// term.c_cc[VTIME] = 0;
	liste = create_list();
	while (42)
	{
		ret = read(0, buffer, 5);
		if (ret > 0)
			fill_list(liste, buffer);
		print_list(liste);
	}
	return(0);
}
