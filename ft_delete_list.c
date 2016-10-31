/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourdon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 18:27:56 by pbourdon          #+#    #+#             */
/*   Updated: 2016/10/21 17:09:21 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		ft_delete_list(t_dlist **p_list)
{
	t_node		*p_temp;
	t_node		*p_del;

	if (p_list != NULL)
	{
		p_temp = (*p_list)->p_head;
		while (p_temp != NULL)
		{
			p_del = p_temp;
			p_temp = p_temp->p_next;
			free(p_del->data);
			free(p_del);
		}
		free(*p_list);
		*p_list = NULL;
	}
}
