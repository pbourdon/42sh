/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 16:03:52 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/17 17:19:24 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int				ft_get_lenght_list(t_history *history)
{
	int			i;

	i = 0;
	while (history)
	{
		i++;
		history = history->next;
	}
	return (i);
}

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

void			show_helper_history(void)
{
	ft_putendl("Syntax:");
	ft_putendl("        history");
	ft_putendl("        history [n]");
	ft_putendl("        history [-crw]");
	ft_putendl("        history -d offset");
	ft_putendl("        history -s arg");
}

void			sub_del_offset(int offset)
{
	t_history	*history;
	t_history	*tmp;
	int			i;

	i = 0;
	history = g_shell.history;
	while (history != NULL && i < offset)
	{
		tmp = history->next;
		if (history->str)
			free(history->str);
		free(history);
		history = tmp;
		i++;
	}
	g_shell.history = history;
	if (history == NULL)
	{
		free(history);
		g_shell.history = malloc(sizeof(*(g_shell.history)));
		g_shell.history->str = NULL;
		g_shell.history->next = NULL;
		g_shell.history->prev = NULL;
	}
}

void			dell_history_offset(t_data *data, char *offset)
{
	int			real_offset;	

	if (offset != NULL)
	{
		real_offset = ft_atoi(offset);
		if (ft_strisdigit(offset) != 0 || real_offset >= ft_get_lenght_list(g_shell.history))
		{
			ft_putstr("sh: history: ");
			ft_putstr(offset);
			ft_putendl(": history position out of range");
			data->binreturn = 255;
			return ;
		}
		sub_del_offset(real_offset);
	}
	else if (offset == NULL)
	{
		ft_putendl("sh: history: -d: option requires an argument");
		show_helper_history();
		data->binreturn = 255;
		return ;
	}
}

void			switch_option(t_data *data, char *str)
{
	int i;

	i = 0;
	if (ft_strcmp(str, "--help") == 0)
		show_helper_history();
	else if (str[2])
	{
		ft_putendl("sh: history: cannot use more than one option");
		show_helper_history();
		data->binreturn = 255;
		return ;
	}
	else if (str[1] == 'c')
		dell_history();
	else if (str[1] == 'd')
		dell_history_offset(data, data->args[2]);
	else if (str[1] == 'i')
	{
		if (data->args[2] == NULL)
			show_history_rev();
		else if (ft_strisdigit(data->args[2]) != -1)
			show_history_rev_until(data->args[2]);
	}
	// if (str[1] == 'r') // add the content of the history file to the history list
// 
	// if (str[1] == 'w') // add the content of the history list to the history file
// 
	// if (str[1] == 's') // add the args to the end of the history list as a single entry
// 
}

int				check_syntax(char **command)
{
	if (command[1] != NULL && (!ft_strisdigit(command[1]) || command[1][0] != '-'))
	{
		ft_putendl("sh: history: illegal usage");
		return (1);
	}
	return (0);
}

void			history(t_data *data)
{
	int			len;

	len = ft_strlentab(data->args);
	if (check_syntax(data->args) == 1)
	{
		show_helper_history();
		data->binreturn = 255;
		return ;
	}
	if (data->args[1] == NULL)
		show_history();
	// else if (data->args[1][0] == '-' && data->args[1][1] != 'r' && len > 2)
	// {
		// data->binreturn = 255;
		// ft_putendl("too many arguments");
		// return ;
	// }
	else if (data->args[1][0] == '-')
		switch_option(data, data->args[1]);
	else if (data->args[1] && ft_strisdigit(data->args[1]) != -1)
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
