/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourdon <pbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 15:00:33 by pbourdon          #+#    #+#             */
/*   Updated: 2016/10/22 09:54:59 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char		*ft_fuck(int *alpha, int index, char *str)
{
	*alpha = *alpha + index;
	return (str);
}

char		*ft_init_values(int *index2, int *pos, char *str, char *values)
{
	*pos = 0;
	*index2 = 0;
	str = ft_strnew(ft_strlen(values) + 1);
	return (str);
}

char		*ft_handle_values(char *values, int i, int *alpha, int index)
{
	char	*str;
	int		index2;
	int		pos;

	str = ft_init_values(&index2, &pos, NULL, values);
	while (values[index] == '\t' || values[index] == ' ')
		index++;
	while (values[index] != '\0')
	{
		ft_bzero(str, ft_strlen(values));
		if (i != 1)
		{
			while (values[index] != ' ' && values[index] != '\0')
				str[index2++] = values[index++];
		}
		else
			while (values[index] != '\0')
				str[index2++] = values[index++];
		str[index2] = '\0';
		if (index2 > 0)
			return (ft_fuck(alpha, index, str));
		index++;
	}
	return (str);
}

void		ft_send_temp_var(t_dlist *list, char *inpu, t_data *data)
{
	t_node		*p_temp;
	char		**tabb;
	char		*tmp;
	char		*tmp2;
	int			index;

	p_temp = list->p_head;
	index = 0;
	tabb = malloc(sizeof(char *) * 1);
	while (p_temp != NULL)
	{
		if (p_temp->data != NULL)
		{
			tmp = ft_strjoin(p_temp->data, "=");
			tmp2 = ft_handle_values(inpu + index, !(p_temp->p_next), &index, 0);
			tmp = ft_joinfree(tmp, tmp2, 1);
			tabb[0] = tmp;
			tabb[1] = NULL;
			checklineok(data, tabb);
			ft_strdel(&tmp);
			ft_strdel(&tmp2);
		}
		p_temp = p_temp->p_next;
	}
	free(tabb);
}

void		ft_read(t_data *data)
{
	int		index;
	char	*str;
	char	*input;
	t_dlist	*list;

	index = 5;
	list = NULL;
	list = dlist_new(list);
	str = ft_get_str_from_tab(data->liste->tabb, 0, 0, 0);
	list = ft_create_list_read(data, list, 1);
	get_next_line(1, &input);
	ft_send_temp_var(list, input, data);
	ft_strdel(&input);
	ft_delete_list(&list);
	ft_strdel(&str);
}
