/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:43:37 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:43:40 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memalloc(size_t size)
{
	void		*new;

	new = malloc(sizeof(void *) * size);
	if (new == NULL)
		return (NULL);
	ft_bzero(new, size);
	return (new);
}
