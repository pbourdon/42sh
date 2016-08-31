/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 18:50:23 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/31 03:30:44 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void			sub_parsecommand2(t_data *data)
{
	if ((ft_strlentab(data->args) == 1) &&
		(ft_strcmp(data->args[0], "$?") == 0))
	{
		if (data->binreturn == 0)
		{
			ft_putnbr(0);
			ft_putendl(": Command not found.");
		}
		else
		{
			ft_putnbr(1);
			ft_putendl(": Command not found.");
		}
	}
}

void			sub_sub_parse(t_data *data)
{
	mainredi(data, 0);
	// free(data->liste);
	// freetab(data->oldtbe);
}

void			sub_parsecommand(t_data *data)
{
	if (ifitsredi(data) != 0)
		return (sub_sub_parse(data));
	else if (checklineok(data, data->args) != -1)
		return ;
	else if (ft_strcmp(data->args[0], "export") == 0)
	{
		insertthetmp(data);
		return ;
	}
	else if (ft_strcmp(data->args[0], "env") == 0)
	{
		callallenv(data);
		return ;
	}
	else if (ft_strcmp(data->args[0], "setenv") == 0)
		callsetenv(data);
	else if (ft_strcmp(data->args[0], "unsetenv") == 0)
		callunsetenv(data);
	else if (ft_strcmp(data->args[0], "cd") == 0)
		cdcall(data);
	else if (ft_strcmp(data->args[0], "history") == 0)
		history(data);
	else
		forkall(data, 0);
	sub_parsecommand2(data);
}

void			exit_func(t_data *data, t_liste *liste)
{
	get_tabhash(NULL, 1);
	if (data->home)
		free(data->home);
	if (data->oldpwd)
		free(data->oldpwd);
	free(data->line);
	freetab(data->args);
	free_list(liste);
	exit(0);
}

int				is_not_spec(char *str)
{
	int i;

	i = -1;
	if (!ft_strcmp(str, "||"))
		return (0);
	if (!ft_strcmp(str, "&&"))
		return (0);
	if (!ft_strcmp(str, "|"))
		return (0);
	if (!ft_strcmp(str, ">"))
		return (0);
	if (!ft_strcmp(str, ">>"))
		return (0);
	if (!ft_strcmp(str, "<"))
		return (0);
	if (!ft_strcmp(str, "<<"))
		return (0);
	return (1);
}

void			find_exit(t_data *data)
{
	int		i;
	int		t;
	char	*tmp;

	t = 0;
	i = 0;
	while (data->args[i])
	{
		ft_putstr("find exit main2 : ");
		ft_putendl(data->args[i]);
		++i;
	}
	--i;
	while (i > 0 && is_not_spec(data->args[i]))
		i--;
	if (!ft_strcmp(data->args[i], "exit"))
	{
		data->exit = 1;
		i++;
		if (data->exit_line != NULL)
			ft_memdel((void **)&data->exit_line);
		if (data->args[i] && is_not_spec(data->args[i]))
			data->exit_line = ft_strdup(data->args[i++]);
		while (data->args[i] && is_not_spec(data->args[i]))
		{
			tmp = data->exit_line;
			data->exit_line = ft_strjoin(data->exit_line, " ");
			free(tmp);
			tmp = data->exit_line;
			data->exit_line = ft_strjoin(data->exit_line, data->args[i]);
			free(tmp);
			i++;
		}
	}
}

void			parsecommand(t_data *data, t_liste *liste)
{
	(void)liste;
	if (data->line[0] == '\0')
	{
		data->dspam = 1;
		return ;
	}
	if (!(data->args = split_on_inib(data->line)))
		return ;
	find_exit(data);
	sub_parsecommand(data);
}

int				switch_case(t_tk *ptr, int nb_redir, int nb_redir2)
{
	if (ptr->tk == 3 && ft_strncmp(ptr->arg, "|", 1) != 0 && ptr->next == NULL)
	{
		ft_putendl("Missing name for redirect.");
		return (-1);
	}
	else if (nb_redir > 1 || nb_redir2 > 1)
	{
		ft_putendl("Ambigous output redirect.");
		return (-1);
	}
	else if (ptr->tk == 3 && ft_strncmp(ptr->arg, "|", 1) == 0
	&& ptr->next == NULL)
	{
		ft_putendl("Invalid null command.");
		return (-1);
	}
	return (0);
}
