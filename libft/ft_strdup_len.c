/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:52:42 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:52:43 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup_len(const char *s1, size_t len)
{
	char	*ret;

	if (!(ret = (char*)ft_memalloc((len + 1) * sizeof(char))))
		return (0);
	ret = ft_strncpy(ret, s1, len);
	return (ret);
}
