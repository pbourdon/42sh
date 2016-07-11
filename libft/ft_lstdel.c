/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:41:35 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:41:36 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*lst;

	if (alst == NULL || *alst == NULL || del == NULL)
		return ;
	lst = *alst;
	while (lst->next)
	{
		del(lst->content, lst->content_size);
		lst = lst->next;
	}
	free(lst);
	*alst = NULL;
}
