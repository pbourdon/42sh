/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 17:15:32 by hlouar            #+#    #+#             */
/*   Updated: 2016/05/23 10:01:00 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*transformtab(char *str)
{
	int		i;
	char	*dst;
	int		o;

	o = 0;
	dst = ft_memalloc(sizeof(char) * ft_strlen(str) + 1);
	i = 0;
	while (str[i])
	{
		while (str[i] == 9)
		{
			dst[o] = ' ';
			i++;
			o++;
		}
		dst[o] = str[i];
		o++;
		i++;
	}
	dst[o] = '\0';
	free(str);
	return (dst);
}

char	*withoutspace(char *str)
{
	int		i;
	char	*dst;
	int		o;
	int		turn;

	turn = 0;
	o = 0;
	dst = (char *)malloc(sizeof(char ) * ft_strlen(str) + 1);
	i = 0;
	while (str[i])
	{
		while ((str[i] == 32 || str[i] == 9) && turn == 0)
		{
			i++;
		}
		turn = 1;
		dst[o] = str[i];
		i++;
		o++;
	}
	dst[o] = '\0';
	free(str);
	return (dst);
}
