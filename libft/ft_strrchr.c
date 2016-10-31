/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 15:25:48 by bde-maze          #+#    #+#             */
/*   Updated: 2015/12/09 16:53:06 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	j;
	int e;

	e = 0;
	j = ft_strlen(s) + 1;
	while (--j)
	{
		if (s[j] == (char)c)
			return ((char*)s + j);
	}
	if (s[j] == (char)c)
		return ((char*)s + j);
	return (NULL);
}
