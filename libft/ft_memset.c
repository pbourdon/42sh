/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 13:21:43 by bde-maze          #+#    #+#             */
/*   Updated: 2015/12/03 17:05:32 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *set, int c, size_t n)
{
	unsigned char		*str;
	size_t				i;

	i = 0;
	str = (unsigned char*)set;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (set);
}
