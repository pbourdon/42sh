/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <pguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 16:03:52 by pguzman           #+#    #+#             */
/*   Updated: 2016/08/05 10:57:48 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*get_history_i(int i)
{
	t_history	*history;
	int			j;

	j = 0;
	history = shell.history;
	while (j < i)
	{
		history = history->next;
		j++;
	}
	return (history->str);
}

void	add_to_history(void)
{
	t_history	*history;

	history = shell.history;
	if (history->str == NULL)
	{
		history->str = ft_strdup(shell.shell_line);
	}
	else
	{
		if (history->next)
		{
			while (history->next)
			{
				history = history->next;
			}
		}
		history->next = malloc(sizeof(*history));
		history->next->str = ft_strdup(shell.shell_line);
		history->next->next = NULL;
	}
}
