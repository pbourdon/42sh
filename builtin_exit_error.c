/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 18:24:05 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/22 18:24:09 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		ft_exit_error(char **s)
{
	unsigned char b;

	b = 0;
	if (s[1])
	{
		if (!ft_isnumber(s[1]))
		{
			ft_putstr_fd("exit: not a numeric argument\n", 2);
			b = 255;
		}
		else
			b = (unsigned char)ft_atoi(s[1]);
		ft_tabdel(&s);
	}
	return (b);
}

int		ft_isnumber(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_tabdel(char ***tb)
{
	long	i;

	if (*tb && **tb)
	{
		i = 0;
		while ((*tb)[i] != NULL)
		{
			free((*tb)[i]);
			++i;
		}
		free(*tb);
		*tb = NULL;
	}
}
