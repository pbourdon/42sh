/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 15:37:59 by hlouar            #+#    #+#             */
/*   Updated: 2016/09/08 15:38:03 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

t_larg		*ft_create_main_list(void)
{
	t_larg *liste;

	liste = malloc(sizeof(t_larg));
	liste->tabb = NULL;
	liste->redi = NULL;
	liste->next = NULL;
	return (liste);
}

void print(t_data *data)
{
	t_larg *liste;
	t_redi *tmp;
	liste = data->argli;
	while (liste)
	{
		if (liste->redi)
			tmp = liste->redi;
		printtab(liste->tabb);
		while (tmp)
		{
		ft_putendl("_____AGREG______");
		if (tmp->agreg)
			ft_putendl(tmp->agreg);
		if (tmp->redi)
			ft_putendl(ft_itoa(tmp->redi));
		ft_putendl("______AGREg_____");
		tmp = tmp->next;
		}
		liste = liste->next;
	}
}

int		redirection_or_not(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return (1);
	else if (ft_strcmp(str, ">>") == 0)
		return (2);
	else if (ft_strcmp(str, "<") == 0)
		return (3);
	else if (ft_strcmp(str, "<<") == 0)
		return (4);
	return (0);
}

int		ft_strlen_for_redi(char **tabb)
{
	int i;

	i = 0;
	while (tabb[i])
	{
		if (redirection_or_not(tabb[i]) > 0)
			return (i);
		i++;
	}
	return (ft_strlentab(tabb));
}

char	**ft_erase_redi_in_tab(char **tabb)
{
	char	**tmp;
	int i;
	int o;

	i = 0;
	o = 0;
	tmp = malloc(sizeof(char *) * (ft_strlen_for_redi(tabb) + 1));
	while (tabb[i])
	{
		if (redirection_or_not(tabb[i]) > 0)
		{
			tmp[o] = NULL;
			return (tmp);
		}
		tmp[o] = ft_strdup(tabb[i]);
		i++;
		o++;
	}
	tmp[o] = NULL;
	return (tmp);
}

void fill_the_main_liste(t_data *data)
{
	t_larg *liste;
	char **tabb;
	int i;

	i = 0;
	data->argli = ft_create_main_list();
	liste = data->argli;
	tabb = ft_strsplit(g_shell.shell_line, '|');
	while (tabb[i] != NULL)
	{
		char *tmp = withoutspace(tabb[i]);
		liste->tabb = ft_strsplit(tmp, ' ');
		if (tabb[i + 1])
		liste->next = malloc(sizeof(t_larg));
		else
		liste->next = NULL;
		liste = liste->next;
		i++;
	}
}

void fill_the_agreg_liste(t_data *data)
{
	t_larg *liste;
	int i;
	int o;
	t_redi *redi;

	liste = data->argli;
	i = 0;
	while (liste)
	{
		liste->redi = malloc(sizeof(t_redi));
		redi = liste->redi;
		o = 0;
		while (liste->tabb[i])
		{
			if (redirection_or_not(liste->tabb[i]) > 0)
			{
				if (o == 0)
				{
					redi->redi = redirection_or_not(liste->tabb[i]);
					redi->agreg = ft_strdup(liste->tabb[i + 1]);
					redi->next = NULL;
					o = 1;
				}
				else
				{
					redi->next = malloc(sizeof(t_redi));
					redi = redi->next;
					redi->agreg = ft_strdup(liste->tabb[i + 1]);
					redi->redi = redirection_or_not(liste->tabb[i]);
					redi->next = NULL;
				}
			}
			i++;
		}
		liste->tabb = ft_erase_redi_in_tab(liste->tabb);
		if (o == 0)
			liste->redi = NULL;
		i = 0;
		liste = liste->next;
	}
}

int		main_fork_redirection(t_larg *liste)
{
	t_redi *tmp;
	int 	out;

	out = 1;
	tmp = liste->redi;
	while (tmp)
	{
		if (tmp->redi == 1)
		{
			out = open(tmp->agreg, O_WRONLY | O_TRUNC |
			O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR | O_APPEND |
			S_IRWXO);
		}
		tmp = tmp->next;
	}
	return (out);
}

int		main_fork_redirection2(t_larg *liste)
{
	t_redi *tmp;
	int 	in;

	in = 0;
	tmp = liste->redi;
	while (tmp)
	{
		if (tmp->redi == 3)
		{
			in = open(tmp->agreg, O_RDONLY);
		}
		tmp = tmp->next;
	}
	return (in);
}

int		main_fork_exec_rediclose(t_data *data, t_larg *liste)
{
	int out;
	int	in;

	in = main_fork_redirection2(liste);
	out = main_fork_redirection(liste);
	ft_putnbr(out);
	freetab(data->args);
	data->args = newtab(liste->tabb);
	dup2(out, 1);
	dup2(in, 0);
	execveremix(data);
	return (1);
}

int		main_fork_exec(t_data *data, t_larg *liste, int pfd[2])
{
	// ft_putendl(liste->tabb[0]);
	// ft_putendl(liste->tabb[1]);
	freetab(data->args);
	data->args = newtab(liste->tabb);
	// ft_putnbr(out);
	if (liste->redi)
		main_fork_exec_rediclose(data, liste);
	// dup2(pfd[1], out);
	// ft_putendl(data->args[0]);
	// ft_putendl(data->args[1]);
	// ft_putendl("____________");
	dup2(pfd[1], 1);
	// dup2(pfd[1], 1);
	close(pfd[0]);
	execveremix(data);
	return (1);
}


int		handle_redir(t_data *data, t_larg *liste)
{
	if (liste->redi->redi == 1)
		main_fork_exec_rediclose(data, liste);
	// else if (liste->redi->redi == 2)
	// 	ft_putendl("redirection 2");
	// else if (liste->redi->redi == 3)
	// 	ft_putendl("redirection 3");
	// else if (liste->redi->redi == 4)
	// 	ft_putendl("redirection 4");
	return (1);
}

void 	main_fork(t_data *data, t_larg *liste)
{
	pid_t father;
	int pfd[2];

	pipe(pfd);
	// if (liste->redi)
	// {
	// 	main_fork_exec_rediclose(data, liste);
	// 	return (main_fork(data, liste->next));
	// }
	if (liste->next == NULL)
	{
		freetab(data->args);
		data->args = newtab(liste->tabb);
		execveremix(data);
		return ;
	}
	if ((father = fork()) == 0)
		main_fork_exec(data, liste, pfd);
	else
		{
			close(pfd[1]);
			dup2(pfd[0], 0);
			return (main_fork(data, liste->next));
		}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(father, NULL, 0);
	return ;
}

void launch_main_fork(t_data *data)
{
	pid_t father;

	father = fork();
	fill_the_main_liste(data);
	fill_the_agreg_liste(data);
	if (father == 0)
		main_fork(data, data->argli);
	else
		wait(0);
}
