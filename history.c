/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <pguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 16:03:52 by pguzman           #+#    #+#             */
/*   Updated: 2016/08/17 17:19:24 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void			dell_history(void)
{
	t_history	*history;
	t_history	*tmp;

	history = g_shell.history;
	while (history != NULL)
	{
		tmp = history->next;
		if (history->str)
			free(history->str);
		free(history);
		history = tmp;
	}
	free(history);
	g_shell.history = malloc(sizeof(*(g_shell.history)));
	g_shell.history->str = NULL;
}

void			switch_option(char *str)
{
	if (ft_strstr(str, "c") != NULL)
		dell_history();
}

void			history(t_data *data)
{
	int			len;

	len = ft_strlentab(data->args);
	if (len > 2)
	{
		ft_putendl("too many arguments");
		return ;
	}
	if (data->args[1] && ft_strisdigit(data->args[1]) != -1)
		show_history_until(data->args[1]);
	if (data->args[1] == NULL)
		show_history();
	else if (ft_strncmp(data->args[1], "-", 0) == 0)
		switch_option(data->args[1]);
}

char			*get_history_i(int i)
{
	t_history	*history;
	int			j;

	j = 0;
	history = g_shell.history;
	while (j < i)
	{
		history = history->next;
		j++;
	}
	return (history->str);
}

void			add_to_history(t_history *his, char *shell_line)
{
	t_history	*history;

	history = his;
	if (history->str == NULL)
		history->str = ft_strdup(shell_line);
	else
	{
		if (history->next)
		{
			while (history->next)
				history = history->next;
		}
		history->next = malloc(sizeof(*history));
		history->next->str = ft_strdup(shell_line);
		history->next->next = NULL;
	}
}
