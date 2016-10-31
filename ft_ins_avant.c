/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ins_avant.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourdon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 01:03:44 by pbourdon          #+#    #+#             */
/*   Updated: 2016/10/21 17:52:44 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

t_node		*fuck42(t_node *courant, char *data)
{
	t_node		*n;

	n = malloc(sizeof(*n));
	if (n != NULL)
	{
		n->data = ft_strdup(data);
		courant->p_next->p_prev = n;
		courant->p_prev->p_next = n;
		n->p_prev = courant->p_prev;
		n->p_next = courant;
	}
	return (courant);
}

t_dlist		*ins_avant(t_dlist *liste, char *data, t_node *courant, int pos)
{
	int			i;

	i = 1;
	while (courant != NULL && i <= pos)
	{
		if (pos == i)
		{
			if (courant->p_next == NULL)
				liste = dlist_append(liste, data);
			else if (courant->p_prev == NULL)
				liste = dlist_prepend(liste, data);
			else
				courant = fuck42(courant, data);
		}
		else
			courant = courant->p_next;
		i++;
	}
	return (liste);
}
