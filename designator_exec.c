/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   designator_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 14:55:51 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/15 18:36:06 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void			design_to_exec(t_data *data, t_liste2 *cur)
{
	int				i;
	t_history		*history;

	i = -1;
	history = g_shell.history;
	ft_putendl(history->str);
	create_command(history->str, cur);
	while (data->args && data->args[++i])
		ft_memdel((void **)&data->args[i]);
	ft_memdel((void **)&data->args);
	if (data->d == 0)
		built_or_launch(data);
	else
	{
		data->args = newtab(cur->tabb);
		execveremix(data);
	}
}
