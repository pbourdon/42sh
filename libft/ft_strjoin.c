/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:53:31 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:53:32 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i;

	if (s1 != NULL && s2 != NULL)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		str = ft_strnew(len);
		i = 0;
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
		str = ft_strcat(str, s2);
		return (str);
	}
	return (NULL);
}
