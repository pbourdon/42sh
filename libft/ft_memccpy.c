/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:41:59 by bde-maze          #+#    #+#             */
/*   Updated: 2015/12/04 18:47:49 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*src;
	unsigned char	e;

	dest = (unsigned char*)s1;
	src = (unsigned char*)s2;
	e = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if ((*dest++ = *src++) == e)
			return (dest);
		i++;
	}
	return (NULL);
}
