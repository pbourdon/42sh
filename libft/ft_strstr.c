/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:56:36 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:56:38 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char		*ft_strstr(const char *s1, const char *s2)
{
	char	*str;

	str = ft_strnstr(s1, s2, ft_strlen(s1));
	return (str);
}
