/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbro.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:49:36 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:49:40 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putnbro(int n, int zero)
{
	unsigned int	nbr;

	if (!zero)
	{
		zero = 1;
		ft_putchar('0');
	}
	if (n < 0)
	{
		nbr = n * -1;
		ft_putchar('-');
	}
	else
		nbr = n;
	if (nbr > 10)
	{
		ft_putnbro(nbr / 10, zero);
		ft_putnbro(nbr % 10, zero);
	}
	else
		ft_putchar(nbr + '0');
}
