/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 10:54:07 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/21 10:58:12 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int			space_nbr(char *str)
{
	int len;

	len = 0;
	while (str && *str)
	{
		if (*str == ' ')
			++len;
		str += 1;
	}
	return (len);
}

int			get_max_and_close_circular_chainlist(t_liste *list)
{
	int			max;
	t_liste		*b;

	b = list;
	max = 0;
	while (list)
	{
		if (max < (int)ft_strlen(list->arg) + space_nbr(list->arg))
			max = (int)ft_strlen(list->arg) + space_nbr(list->arg);
		if (!list->next || list->next == b)
		{
			list->next = b;
			break ;
		}
		list = list->next;
	}
	return (max);
}

void		ft_put_nd_add_backslash_on_str(char *str)
{
	while (str && *str)
	{
		if (*str == ' ')
			ft_putstr("\\");
		write(1, str, 1);
		str += 1;
	}
}

int			print_padded_list2(t_liste *list, t_liste *tmp, int col, int max)
{
	int		h;
	int		l;

	h = 1;
	l = 0;
	while (list->next != tmp)
	{
		ft_put_nd_add_backslash_on_str(list->arg);
		if ((++h) % col)
		{
			if (ft_strlen(list->arg) < (size_t)max)
				write(1, "                              ", \
					max - (ft_strlen(list->arg) + space_nbr(list->arg)));
			ft_putstr("     ");
		}
		else if ((++l))
			ft_putstr("\n");
		list = list->next;
		if (list->next == tmp)
			ft_putstr(list->arg);
	}
	ft_putstr("\n");
	return (l + 1);
}

int			print_padded_list(t_liste *list, int col, int max)
{
	t_liste *tmp;

	press_end_key();
	write(1, "\n", 1);
	while (list != list->next && ft_strcmp(list->arg, list->next->arg) < 0)
	{
		list = list->next;
		if (ft_strcmp(list->arg, list->next->arg) > 0)
		{
			list = list->next;
			break ;
		}
	}
	tmp = list;
	if (list->next == tmp)
		ft_put_nd_add_backslash_on_str(list->arg);
	return (print_padded_list2(list, tmp, col, max));
}
