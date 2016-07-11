/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:40:43 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:40:45 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*ft_convert_int(char *str, int n, int i, int size)
{
	int				tmp;

	tmp = n;
	size = 1;
	while (tmp / 10 > 0)
	{
		size *= 10;
		tmp /= 10;
	}
	while (size > 0)
	{
		tmp = n / size;
		n %= size;
		size /= 10;
		str[i++] = tmp + '0';
	}
	str[i] = '\0';
	return (str);
}

char				*ft_itoa(int n)
{
	int				i;
	int				size;
	char			*str;

	size = 1;
	str = (char *)malloc(13);
	i = 0;
	if (n < 0)
	{
		str[i] = '-';
		n *= -1;
		i++;
	}
	str = ft_convert_int(str, n, i, size);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	return (str);
}
