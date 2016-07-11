/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:50:32 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:50:33 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_realloc(void *ptr, size_t size)
{
	void	*p_ptr;

	if (!ptr)
		return (ft_memalloc(size));
	if (!size)
		return (ptr);
	if (!(p_ptr = ft_memalloc(size)))
		return (ptr);
	ft_memcpy(p_ptr, ptr, size);
	free(ptr);
	ptr = NULL;
	return (p_ptr);
}
