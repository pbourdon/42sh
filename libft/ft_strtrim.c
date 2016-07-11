/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 11:53:27 by bde-maze          #+#    #+#             */
/*   Updated: 2016/04/27 11:53:29 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char	*trimend(char *str)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (ft_isspace(str[i]))
		str[i--] = '\0';
	return (str);
}

char		*ft_strtrim(char const *s)
{
	char	*str;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	str = ft_strsub(s, i, ft_strlen(s));
	str = trimend(str);
	return (str);
}
