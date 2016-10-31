/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourdon <pbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 15:00:33 by pbourdon          #+#    #+#             */
/*   Updated: 2016/10/22 09:54:07 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			ft_put_error_read(void)
{
	ft_putstr("read: usage: read [-rs] [-u fd] [-t timeout] [-p prompt] [-n ");
	ft_putstr("nchars] [name ...]\n");
}

char			*ft_get_str_from_tab(char **tabb, int index2, int index3,
				int index)
{
	int			len;
	char		*str;

	len = 0;
	while (tabb[index])
	{
		len += ft_strlen(tabb[index]);
		index++;
	}
	str = malloc(sizeof(char) * len + 1);
	index = 0;
	while (tabb[index])
	{
		while (tabb[index][index2] != '\0')
			str[index3++] = tabb[index][index2++];
		str[index3++] = ' ';
		index++;
		index2 = 0;
	}
	index3--;
	str[index3] = '\0';
	return (str);
}

t_dlist			*ft_create_list_read(t_data *data, t_dlist *alpha,
				int pos)
{
	char		**tabb;

	tabb = data->liste->tabb;
	while (tabb[pos] != '\0')
	{
		alpha = ft_add_data(alpha, tabb[pos]);
		pos++;
	}
	return (alpha);
}
