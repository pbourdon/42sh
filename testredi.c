/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testredi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <hlouar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 15:25:49 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/25 14:52:31 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		mainpipehelp(t_data *data, t_liste2 *liste)
{
	if (liste->redi == 6)
	{
		agreve(data, liste);
		return (4);
	}
	else if (mainpipecond(data, liste) != -1)
	{
		exit(0);
		return (6);
	}
	else if (mainpipehelp2(data, liste) != -1)
	{
		exit(45);
		return (2);
	}
	else if (liste->next->next == NULL)
	{
		if (createbinpath(data, 2) == 0)
			return (5);
		freetab(data->args);
		data->args = newtab(liste->tabich);
		execveremix(data);
		return (1);
	}
	return (0);
}

int		mainpipe(t_data *data, t_liste2 *liste)
{
	pid_t	father;
	int		pfd[2];

	pipe(pfd);
	if (mainpipehelp(data, liste) != 0)
	{
		close(pfd[0]);
		close(pfd[1]);
	}
	if ((father = fork()) == 0)
		childhelp(data, liste, pfd);
	else
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		if (liste->redi == 3 || liste->redi == 8)
			return (mainpipe(data, liste->next->next));
		else
			return (mainpipe(data, liste->next));
	}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(father, NULL, 0);
	return (1);
}

int		optchev2(t_data *data, int i, char *str)
{
	int		o;
	char	**tabich;
	char	*line;
	int		fd;

	o = 0;
	if (optchev(data) == 1)
	{
		fd = open(str, O_RDWR);
		while (get_next_line(fd, &line) > 0)
		{
			free(line);
			i++;
		}
		free(line);
		close(fd);
		fd = open(str, O_RDWR);
		tabich = (char **)malloc(sizeof(char *) * (i + 1));
		while (get_next_line(fd, &line) > 0)
		{
			tabich[o] = ft_strdup(line);
			free(line);
			o++;
		}
		free(line);
		close(fd);
		tabich[o] = NULL;
		data->tabchev = newtab(tabich);
		freetab(tabich);
	}
	return (1);
}

int		thereisadoubleleft(t_data *data)
{
	int i;

	i = 0;
	while (data->oldtbe[i])
	{
		if (ft_strcmp(data->oldtbe[i], "<<") == 0)
			return (1);
		i++;
	}
	return (-1);
}

void free_liste2(t_liste2 *ptr)
{
	t_liste2		*tmp;

	while (ptr->next != NULL)
	{
		tmp = ptr->next;
		freetab(ptr->tabich);
		free(ptr);
		ptr = tmp;
	}
	free(ptr);
}

int		mainredi(t_data *data, int i)
{
	int		father;
	char	*str;

	data->liste = createliste();
	data->oldtbe = newtab(data->args);
	str = ft_strdup(data->args[(ft_strlentab(data->args) - 1)]);
	argliste(data);
	if (movecd(data) == 2)
		return (1);
	freetab(data->args);
	data->args = newtab(data->oldtbe);
	optchev2(data, i, str);
	free(str);
	if (ifitsredi(data) != 0)
	{
		father = fork();
		if (father == 0)
		{
			mainpipe(data, data->liste);
			exit(0);
		}
		else
		{
			wait(0);
			ft_reset_term(g_shell.term_reset.term);
		}
	}
	else
		return(1);
	return (1);
}
