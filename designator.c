/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   designator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 13:31:53 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/05 13:32:06 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int			check_syntax_designator(t_data *data)
{
	if (data->args[0][0] == '!')
	{
		if (data->args[0][1] && data->args[0][1] != ' ')
			return (0);
	}
	return (-1);
}

void		designator(t_data *data)
{
	(void)data;
	ft_putendl("hello designator");

}