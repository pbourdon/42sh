/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_designator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourdon <pbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 18:46:35 by pbourdon          #+#    #+#             */
/*   Updated: 2016/10/18 12:19:10 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char				*ft_replace_designator_norm(int number, char *command2,
	int display)
{
	t_history		*history;
	int				i;

	i = 1;
	if (number < 0)
		return (ft_error_event_char(command2, display));
	history = g_shell.history;
	if (!history->str)
		return (ft_error_event_char(command2, display));
	while (i <= number && history)
	{
		i++;
		history = history->next;
	}
	if (i < number)
		return (ft_error_event_char(command2, display));
	if (!history || !history->str)
		return (ft_error_event_char(command2, display));
	return (ft_strdup(history->str));
}

char				*ft_replace_designator_rev(int number, char *command2,
	int display)
{
	t_history		*history;

	if (number == 0 || number == -0)
		return (ft_error_event_char(command2, display));
	number = -number - 1;
	history = g_shell.history;
	if (!history->str)
		return (ft_error_event_char(command2, display));
	while (history->next)
		history = history->next;
	while (history && number-- > 0)
		history = history->prev;
	if (!history || !history->str)
		return (ft_error_event_char(command2, display));
	return (ft_strdup(history->str));
}

char				*ft_replace_designator4(char *command, char *command2,
	int display)
{
	t_history		*history;
	int				index;

	index = 0;
	while (command[index] != '\0' && command[index] != ' ' &&
		command[index] != '\t')
		index++;
	if (command == NULL)
		return (ft_error_event_char(command2, display));
	history = g_shell.history;
	if (!history->str)
		return (ft_error_event_char(command2, display));
	while (history->next)
		history = history->next;
	while (history && ft_strncmp(history->str, command, index))
		history = history->prev;
	if (!history || !history->str)
		return (ft_error_event_char(command2, display));
	return (ft_strdup(history->str));
}

char				*ft_replace_designator5(char *command, char *command2,
	int display)
{
	t_history		*history;
	char			*str;

	str = NULL;
	str = ft_strdup_special(command, str);
	if (command == NULL)
		return (ft_error_event_char2(command2, display, str));
	history = g_shell.history;
	if (!history->str)
		return (ft_error_event_char2(command2, display, str));
	while (history->next)
		history = history->next;
	while (history && ft_strstr(history->str, str) == NULL)
		history = history->prev;
	if (!history || !history->str)
		return (ft_error_event_char2(command2, display, str));
	ft_strdel(&str);
	return (ft_strdup(history->str));
}

char				*ft_replace_designator6(char *command)
{
	int				index;
	char			*retur;

	if (command == NULL)
		return (NULL);
	index = 0;
	retur = malloc(sizeof(char) * ft_strlen(command) + 1);
	while (command[index] != '\0')
	{
		if (command[index] == '!' && command[index + 1] == '#')
		{
			index = ft_strlen(command);
		}
		else
		{
			retur[index] = command[index];
			index++;
		}
	}
	return (retur);
}
