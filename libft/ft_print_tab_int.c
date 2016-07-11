/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klonger <klonger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 11:42:38 by klonger           #+#    #+#             */
/*   Updated: 2015/02/19 00:33:28 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_print_tab_int(int *tab, int size)
{
	int		x;

	x = 0;
	if (tab)
		while (x < size)
		{
			ft_putnbr(tab[x]);
			x++;
		}
	ft_putchar('\n');
}
