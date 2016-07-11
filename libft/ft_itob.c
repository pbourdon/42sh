/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:40:52 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:40:55 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itob(int n)
{
	int		i;
	int		b;
	char	*bin;

	bin = (char *)malloc(sizeof(char) * 13);
	i = 11;
	while (i >= 0)
	{
		if (n >= 0)
		{
			b = n % 2;
			n /= 2;
			bin[i] = b + '0';
		}
		else
			bin[i] = 0;
		i--;
	}
	bin[12] = '\0';
	return (bin);
}
