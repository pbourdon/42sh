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

#include <stdio.h>

void			read_loop(int out)
{
	t_history	*history;
	char	 	*line;
	int			i = 0;

	history = g_shell.history;
	while (get_next_line(out, &line) > 0)
	{
		ft_putnbr(i);
		ft_putstr("\n");
		if (history == NULL)
			history = malloc(sizeof(*history));
		history->str = ft_strdup(line);
		history->next->prev = history;
		history = history->next;
		history->next = NULL;
		i++;
	}
		// history->next = malloc(sizeof(*(history)));
		// history->str = ft_strdup(line);
		// history = history->next;
		// history->prev = history;
		// history->next = NULL;
		// history->str = NULL;
	// }
	while (g_shell.history)
		g_shell.history = g_shell.history->prev;
	// free(line);
}

int				append_to_list()
{
	t_history	*tmp;
	int			out;

	out = open(".ftsh_history", O_RDWR);
	if (out < 0)
		return (-1);
	dell_history();
	read_loop(out);
	tmp = g_shell.history;
	while (tmp)
	{
		printf("tmp: %p, tmp->str: %p, str: %s, tmp->next: %p\n", tmp, tmp->str, tmp->str, tmp->next);
		ft_putendl(tmp->str);
		tmp = tmp->next;
	}
	return (0);
}

void			add_arg_to_history(t_data *data)
{
	int			i;

	i = 2;
	if (data->args[2] == NULL)
	{
		ft_putendl("sh: history: give at least one argument");
		show_helper_history();
		data->binreturn = 255;
		return ;
	}
	while (data->args[i])
		add_to_history(g_shell.history, data->args[i++]);
}

void			append_to_file()
{
	t_history	*history;
	int			fd;

	history = g_shell.history;
	fd = open(".ftsh_history", O_WRONLY | O_TRUNC |
		O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR);
	while (history)
	{
		ft_putendl_fd(history->str, fd);
		history = history->next;
	}
}

void			switch_option_2(t_data *data, char *str)
{
	// if (str[1] == 'r')
	// {
		// if (append_to_list() == -1)
		// {
			// ft_putendl("sh: history: no history source file");
			// data->binreturn = 255;
		// }
	// }
	if (str[1] == 'w')
		append_to_file();
	if (str[1] == 's')
		add_arg_to_history(data);
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
	else
		switch_option_2(data, str);
}

int				check_syntax(char **command)
{
	if (command[1] != NULL && (!ft_strisdigit(command[1]) || command[1][0] != '-'))
	{
		ft_putendl("sh: history: illegal usage");
		return (1);
	}
	if ((command[1] != NULL && command[1][0] == '-') && (command[1][1] != 'c'
		&& command[1][1] != 'r' && command[1][1] != 'w'
		&& command[1][1] != 'd' && command[1][1] != 's'))
	{
		ft_putstr("sh: history: ");
		ft_putstr(command[1]);
		ft_putendl(": invalid option");
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
