/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:44:19 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:44:21 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	const unsigned char	*tmp_src;
	unsigned char		*tmp_dst;

	tmp_dst = dst;
	tmp_src = src;
	i = 0;
	while (i < n)
	{
		tmp_dst[i] = tmp_src[i];
		if (tmp_dst[i] == (unsigned char)c)
			return (&tmp_dst[i + 1]);
		i++;
	}
	return (NULL);
}
