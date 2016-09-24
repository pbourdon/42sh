/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   designator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 13:31:53 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/24 17:17:52 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		create_command(char *command, t_liste2 *liste)
{
	free(liste->tabb[0]);
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
	while (history && i > len)
	{
		i--;
		history = history->prev;
	}
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
	ft_putendl(history->str);
	create_command(history->str, cur);
	i = -1;
	while (data->args && data->args[++i])
		ft_memdel((void **)&data->args[i]);
	ft_memdel((void **)&data->args);
	if (data->d == 0)
		built_or_launch(data);
	else
	{
		data->args = newtab(cur->tabb);
		execveremix(data, cur);
	}
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
	ft_putendl(history->str);
	create_command(history->str, cur);
	i = -1;
	while (data->args && data->args[++i])
		ft_memdel((void **)&data->args[i]);
	ft_memdel((void **)&data->args);
	if (data->d == 0)
		built_or_launch(data);
	else
	{
		data->args = newtab(cur->tabb);
		execveremix(data, cur);
	}
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
