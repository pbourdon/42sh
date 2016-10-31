/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 13:35:52 by bde-maze          #+#    #+#             */
/*   Updated: 2016/10/17 15:39:41 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(*new_str) * (ft_strlen(src) + 1));
	if (new_str == NULL)
		return (NULL);
	return (ft_strcpy(new_str, src));
}
