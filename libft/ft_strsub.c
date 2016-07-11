/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:56:47 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:56:48 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;

	if (s != NULL)
	{
		str = (char *)malloc(sizeof(char) * len + 1);
		if (str == NULL)
			return (NULL);
		i = 0;
		while (start < ft_strlen(s) && i < len)
		{
			str[i] = s[start];
			i++;
			start++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
