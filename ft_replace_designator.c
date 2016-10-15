/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_designator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourdon <pbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 18:46:35 by pbourdon          #+#    #+#             */
/*   Updated: 2016/10/15 19:00:51 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char				*ft_replace_designator_norm(int number, char *command2)
{
	t_history		*history;
	int				i;

	i = 1;
	if (number < 0)
		return (ft_error_event_char(command2));
	history = g_shell.history;
	if (!history->str)
		return (ft_error_event_char(command2));
	while (i <= number && history)
	{
		i++;
		history = history->next;
	}
	if (i < number)
		return (ft_error_event_char(command2));
	if (!history || !history->str)
		return (ft_error_event_char(command2));
	return (history->str);
}

char				*ft_replace_designator_rev(int number, char *command2)
{
	t_history		*history;

	if (number == 0 || number == -0)
		return (ft_error_event_char(command2));
	number = -number - 1;
	history = g_shell.history;
	if (!history->str)
		return (ft_error_event_char(command2));
	while (history->next)
		history = history->next;
	while (history && number-- > 0)
		history = history->prev;
	if (!history || !history->str)
		return (ft_error_event_char(command2));
	return (history->str);
}

char				*ft_replace_designator4(char *command, char *command2)
{
	t_history		*history;

	if (command == NULL)
		return (ft_error_event_char(command2));

	history = g_shell.history;
	if (!history->str)
		return (ft_error_event_char(command2));
	while (history->next)
		history = history->next;
	while (history && ft_strncmp(history->str, command, ft_strlen(command)))
		history = history->prev;
	if (!history || !history->str)
		return (ft_error_event_char(command2));
	return (history->str);
}

char				*ft_replace_designator5(char *command, char *command2)
{
	t_history		*history;

	if (command == NULL)
		return (ft_error_event_char(command2));
	history = g_shell.history;
	if (!history->str)
		return (ft_error_event_char(command2));
	while (history->next)
		history = history->next;
	while (history && ft_strstr(history->str, command) == NULL)
		history = history->prev;
	if (!history || !history->str)
		return (ft_error_event_char(command2));
	return (history->str);
}
char				*ft_replace_designator6(char *command)
{
	int				index;
	char			*retur;

	index = 0;
	retur = malloc(sizeof(char) * ft_strlen(command) + 1);
	while (command[index] != '\0' &&
			(command[index] != '!' && command[index + 1] != '#'))
	{
		retur[index] = command[index];
		index++;
	}
	return (retur);
}
