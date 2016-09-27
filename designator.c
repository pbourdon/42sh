/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   designator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 13:31:53 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/27 15:04:12 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		create_command(char *command, t_liste2 *liste)
{
	int i;
	int t;

	t = 0;
	i = -1;
	while (command[++i])
		if (command[i] == '|')
			t = i;
	free(liste->tabb[0]);
	if (t != 0 && t < i - 3)
		liste->tabb[0] = ft_strdup(command + t + 3);
	else
		liste->tabb[0] = ft_strdup(command);
}

void		design_to_index_rev(t_data *data, int index, t_liste2 *cur)
{
	t_history	*history;
	int			i;
	int			len;

	i = g_shell.history_index;
	history = g_shell.history;
	len = i - index;
	if (!history->str)
		return (send_error(data));
	while (history->next)
		history = history->next;
	while (history && i-- > len)
		history = history->prev;
	if (i > len)
	{
		ft_putstr_fd("sh: ", 2);
		ft_putstr_fd(data->args[0], 2);
		ft_putendl_fd(": event not found", 2);
		data->binreturn = 255;
		return ;
	}
	if (!history || history->str)
		return (send_error(data));
	return (design_to_exec(data, cur));
}

void		design_to_index(t_data *data, int index, t_liste2 *cur)
{
	t_history	*history;
	int			i;

	i = 1;
	history = g_shell.history;
	if (!history->str)
		return (send_error(data));
	while (i < index && history)
	{
		i++;
		history = history->next;
	}
	if (i < index)
	{
		ft_putstr_fd("sh: ", 2);
		ft_putstr_fd(data->args[0], 2);
		ft_putendl_fd(": event not found", 2);
		data->binreturn = 255;
		return ;
	}
	if (!history || history->str)
		return (send_error(data));
	return (design_to_exec(data, cur));
}

int			check_syntax_designator(t_data *data)
{
	if (data->args[0][0] == '!')
	{
		if (data->args[0][1] == '!' && data->args[0][2])
			return (-1);
		if (data->args[0][1] && data->args[0][1] != ' ')
			return (0);
	}
	return (-1);
}

void		designator(t_data *data, t_liste2 *cur)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ft_isdigit(data->args[0][1]) ||
		(data->args[0][1] == '-' && ft_isdigit(data->args[0][2])))
	{
		tmp = data->args[0];
		if (ft_strisdigit(++tmp) == 0)
			design_to_index(data, ft_atoi(tmp), cur);
		else if (ft_strisdigit(++tmp) == 0)
			design_to_index_rev(data, ft_atoi(tmp), cur);
	}
	else if (ft_strcmp(data->args[0], "!!") == 0)
		design_to_index_rev(data, 1, cur);
	else if (data->args[0][1] == '?')
		design_to_string(data, data->args[0], 0, cur);
	else
		design_to_start_string(data, data->args[0], 0, cur);
}
