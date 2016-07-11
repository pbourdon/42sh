/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:45:16 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:45:18 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*str;

	str = (unsigned char *)malloc(sizeof(unsigned char) * len);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, src, len);
	ft_memcpy(dst, str, len);
	free(str);
	return (dst);
}
