/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:45:37 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:47:38 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_pow(int nb, int power)
{
	int		res;

	res = 1;
	if (power < 0)
		return (0);
	else if (power > 0)
		res = nb * ft_pow(nb, power - 1);
	return (res);
}
