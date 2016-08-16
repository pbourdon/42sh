/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_letter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 15:59:27 by pguzman           #+#    #+#             */
/*   Updated: 2016/08/03 16:01:42 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		ft_strlend(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	delete_last_backslash(void)
{
	shell.shell_line = del_from_arr(shell.shell_line, shell.length_line);
}

int		get_history_length(void)
{
	t_history	*history;
	int			i;

	history = shell.history;
	if (history->str)
		i = 1;
	else
		i = 0;
	while (history->next)
	{
		history = history->next;
		i++;
	}
	return (i);
}
