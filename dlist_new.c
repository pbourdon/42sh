/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourdon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 15:35:22 by pbourdon          #+#    #+#             */
/*   Updated: 2016/10/19 16:11:17 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

t_dlist		*dlist_new(t_dlist *p_new)
{
	p_new = malloc(sizeof(*p_new));
	if (p_new != NULL)
	{
		p_new->p_head = NULL;
		p_new->p_tail = NULL;
	}
	return (p_new);
}
