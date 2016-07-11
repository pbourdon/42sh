/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:44:52 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:44:53 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	const char	*tmp_src;
	char		*tmp_dst;

	tmp_src = src;
	tmp_dst = dst;
	if (n == 0 || dst == src)
		return (dst);
	i = 0;
	while (i < n)
	{
		tmp_dst[i] = tmp_src[i];
		i++;
	}
	return (tmp_dst);
}
