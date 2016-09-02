/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 18:50:23 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/31 10:52:28 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

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
	if (!ft_strcmp(str, "<"))
		return (0);
	if (!ft_strcmp(str, "<<"))
		return (0);
	return (1);
}

void			find_exit(t_data *data, int i, char *tmp)
{
	while (data->args[i])
		++i;
	--i;
	while (i > 0 && is_not_spec(data->args[i - 1]))
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
	find_exit(data, 0, NULL);
	sub_parsecommand(data, 0);
	// ft_putstr("valeur de retour: ");
	// ft_putnbr(data->binreturn);
	// ft_putstr("\n");

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
