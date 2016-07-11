/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basenbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:37:27 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:37:31 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_basenbr(int n, int base)
{
	int		i;
	int		nbase;

	i = 0;
	nbase = 0;
	while (n > 0)
	{
		nbase += (n % base) * ft_pow(10, i);
		n /= base;
		i++;
	}
	return (nbase);
}
