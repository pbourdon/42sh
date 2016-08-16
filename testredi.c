/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testredi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 15:25:49 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/16 16:05:30 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		agreve(t_data *data, t_liste2 *liste)
{
	char	*dst;
	char	*str;
	int		a;
	int		b;

	str = decoupe1(data->oldtbe[ft_strlentab(data->oldtbe) - 1]);
	dst = decoupe2(data->oldtbe[ft_strlentab(data->oldtbe) - 1]);
	a = ft_atoi(dst);
	b = ft_atoi(str);
	if (ft_strcmp(dst, "-") == 0)
		close(b);
	if (!(isatty(a)))
	{
		ft_putstr("csh: ");
		ft_putstr(dst);
		ft_putendl(": bad file descriptor");
		exit(0);
	}
	free(str);
	free(dst);
	dup2(b, a);
	freetab(data->args);
	data->args = newtab(liste->tabich);
	execveremix(data);
	exit(0);
}

int		mainpipehelp(t_data *data, t_liste2 *liste)
{
	if (liste->redi == 1)
	{
		helpall2(data, liste);
		return (1);
	}
	else if (liste->redi == 2)
	{
		doubleredichieh(data, liste);
		return (5);
	}
	else if (liste->redi == 6)
	{
		agreve(data, liste);
		exit(0);
	}
	else if (mainpipehelp2(data, liste) != -1)
		return (2);
	else if (liste->next->next == NULL)
	{
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
		return (5);
	}
	if ((father = fork()) == 0)
		childhelp(data, liste, pfd);
	else
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		if (liste->redi == 3)
			return (mainpipe(data, liste->next->next));
		else
			return (mainpipe(data, liste->next));
	}
	close(pfd[0]);
	close(pfd[1]);
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
