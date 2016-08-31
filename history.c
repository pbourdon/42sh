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

#include "includes/shell.h"

int				ft_strisdigit(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

void			switch_option(t_data *data, char *str)
{
	if (ft_strstr(str, "c") != NULL)
		dell_history();
	if (ft_strstr(str, "r") != NULL)
	{
		if (data->args[2] == NULL)
			show_history_rev();
		else
			show_history_rev_until(data->args[2]);
	}
}

void			history(t_data *data)
{
	int			len;

	len = ft_strlentab(data->args);
	if (data->args[1] == NULL)
		show_history();
	else if (ft_strncmp(data->args[1], "-", 0) == 0 && (data->args[2] == NULL ||
		(data->args[2] && ft_strisdigit(data->args[2]) != -1)))
		switch_option(data, data->args[1]);
	else if (len > 2)
	{
		ft_putendl("too many arguments");
		return ;
	}
	if (data->args[1] && ft_strisdigit(data->args[1]) != -1)
		show_history_until(data->args[1]);
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
		history->next->prev = history;
		history->next->next = NULL;
	}
}
