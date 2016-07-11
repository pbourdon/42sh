/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:36:35 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:36:43 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_char_to_escape(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\r' ||
			c == '\f')
		return (1);
	return (0);
}

int				ft_atoi(const char *str)
{
	int			i;
	int			is_negative;
	int			value;

	is_negative = 0;
	value = 0;
	i = 0;
	while (is_char_to_escape(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		is_negative = 1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		value = (value * 10) - (str[i] - '0');
		i++;
	}
	if (!is_negative)
		value *= -1;
	return (value);
}
