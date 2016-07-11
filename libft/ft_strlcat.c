/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:53:42 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:53:43 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	i;

	len_dst = ft_strlen(dst);
	i = 0;
	if (size >= len_dst)
	{
		while (len_dst < size - 1)
			dst[len_dst++] = src[i++];
		dst[len_dst] = '\0';
		return (len_dst + ft_strlen(src) - i);
	}
	return (size + ft_strlen(src));
}
