/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:45:25 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:45:26 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*uc;

	if (len && b)
	{
		uc = (unsigned char *)b;
		i = 0;
		while (i < len)
			uc[i++] = (unsigned char)c;
	}
	return (b);
}
