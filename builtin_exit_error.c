/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 18:24:05 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/31 11:41:16 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		ft_exit_error(t_data *data, int *out)
{
	unsigned char b;

	*out = 1;
	b = 0;
	if (data->exit_line)
	{
		if (ft_isnumber(data->exit_line))
			b = (unsigned char)ft_atoi(data->exit_line);
		else if (data->exit_line[0] == '-' && data->exit_line[1] && \
		ft_isnumber(&data->exit_line[1]))
			b = (unsigned char)ft_atoi(data->exit_line);
		else if (data->exit_line[0] == '-' && data->exit_line[1] == '-')
		{
			ft_putstr_fd("exit: Badly formed number.\n", 2);
			*out = 0;
		}
		else
		{
			ft_putstr_fd("exit: Expression Syntax.\n", 2);
			*out = 0;
		}
		ft_strdel(&data->exit_line);
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
