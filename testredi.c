/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testredi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 15:25:49 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/18 17:51:18 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		mainpipehelp(t_data *data, t_liste2 *liste)
{
	if (liste->redi == 6)
	{
		agreve(data, liste);
		exit(0);
	}
	else if (mainpipecond(data, liste) != -1)
	{
		return (6);
	}
	else if (mainpipehelp2(data, liste) != -1)
		return (2);
	else if (liste->next->next == NULL)
	{
		if (createbinpath(data, 2) == 0)
		{
			ft_putstr(data->args[0]);
			ft_putendl(": Command not found");
			exit(0);
		}
		freetab(data->args);
		data->args = newtab(liste->tabich);
		execveremix(data);
		return (1);
	}
	return (0);
}

int	checkifbinexist(t_data *data, t_liste2 *liste)
{
	t_liste2 *tmp;

	tmp = liste;
	int i;
	int o;

	o = 0;
	i = 0;
	while (tmp->next)
	{
		if (tmp->redi == 5)
			o = 1;
		freetab(data->args);
		data->args = newtab(tmp->tabich);
		if (tmp->redi == 2 || tmp->redi == 1)
			return (0);
		if (createbinpath(data, 2) == 0 && o == 1)
		{
				i = 1;
				ft_putstr(tmp->tabich[0]);
				ft_putendl(": Command not found");
		}
		tmp = tmp->next;
	}
	if (i == 1)
		return (1);
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
	{
		childhelp(data, liste, pfd);
	}
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
			i++;
		close(fd);
		fd = open(str, O_RDWR);
		tabich = (char **)malloc(sizeof(char *) * (i + 1));
		while (get_next_line(fd, &line) > 0)
		{
			tabich[o] = ft_strdup(line);
			o++;
		}
		tabich[o] = NULL;
		data->tabchev = newtab(tabich);
		freetab(tabich);
		close(fd);
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

int		mainredi(t_data *data)
{
	int		father;
	int		i;
	char	*str;

	i = 0;
	data->liste = createliste();
	data->oldtbe = newtab(data->args);
	father = fork();
	str = ft_strdup(data->args[(ft_strlentab(data->args) - 1)]);
	optchev2(data, i, str);
	free(str);
	if (ifitsredi(data) != 0)
	{
		if (father == 0)
		{
			argliste(data);
			mainpipe(data, data->liste);
			freeliste(data->liste);
			exit(0);
		}
		else
			wait(0);
	}
	return (1);
}
