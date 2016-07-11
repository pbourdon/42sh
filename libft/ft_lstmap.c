/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:42:56 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:42:57 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*begin;

	begin = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		tmp = f(lst);
		if (!begin)
			begin = tmp;
		else
			ft_lstend(begin)->next = tmp;
		lst = lst->next;
	}
	return (begin);
}
