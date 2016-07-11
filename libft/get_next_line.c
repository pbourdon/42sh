/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 19:19:42 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 19:19:54 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_save(char *buf, char **tmp, char *save)
{
	int i;
	int j;

	i = ft_strlen(*tmp);
	j = 0;
	*tmp = ft_realloc(*tmp, (ft_strlen(*tmp) + ft_strlen(buf) + 1));
	while (buf[j] != '\0')
	{
		if (buf[j] == '\n')
		{
			*((*tmp) + i) = '\0';
			save = ft_strcpy(save, &buf[++j]);
			return (1);
		}
		tmp[0][i++] = buf[j++];
	}
	ft_bzero(save, ft_strlen(save));
	*((*tmp) + i) = '\0';
	return (0);
}

static int	free_and_return(char **buf, char **tmp, char **line)
{
	*line = ft_strdup(*tmp);
	free(*buf);
	*buf = NULL;
	free(*tmp);
	*tmp = NULL;
	if (line[0] == '\0')
		return (0);
	return (1);
}

static void	free_and_free(char **buf, char **tmp)
{
	free(*buf);
	*buf = NULL;
	free(*tmp);
	*tmp = NULL;
}

int			get_next_line(int const fd, char **line)
{
	int			ret;
	char		*buf;
	char		*tmp;
	static char save[BUFF_SIZE];

	if (fd == -1)
		return (-1);
	buf = ft_memalloc(BUFF_SIZE + 1);
	tmp = ft_memalloc(BUFF_SIZE + 1);
	if (!tmp || !buf)
		return (-1);
	if (check_save(save, &tmp, save) == 1)
		return (free_and_return(&buf, &tmp, line));
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (check_save(buf, &tmp, save) == 1)
			return (free_and_return(&buf, &tmp, line));
	}
	if (ret == -1)
		return (-1);
	if (ret == 0 && tmp[0] != '\0')
		return (free_and_return(&buf, &tmp, line));
	free_and_free(&buf, &tmp);
	return (0);
}
