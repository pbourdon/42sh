/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 15:24:09 by bde-maze          #+#    #+#             */
/*   Updated: 2015/12/09 16:52:02 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *aig, size_t n)
{
	size_t	i;
	size_t	j;
	int		e;

	i = 0;
	j = 0;
	e = 0;
	if (aig[0] == '\0')
		return (char *)(src);
	while (i < n && src[i])
	{
		j = i;
		e = 0;
		while (src[j] == aig[e] && j < n)
		{
			e++;
			j++;
			if (aig[e] == '\0')
				return ((char *)&src[i]);
		}
		i++;
	}
	return (0);
}
