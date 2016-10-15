/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecommand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 15:10:39 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/15 18:30:32 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int				design_norm(t_data *data)
{
	int i;

	i = -1;
	while (data->args && data->args[++i])
		ft_memdel((void **)&data->args[i]);
	if (data->args)
		ft_memdel((void **)&data->args);
	data->args = newtab(data->liste->tabb);
	i = -1;
	while (data->args && data->args[++i])
		ft_memdel((void **)&data->args[i]);
	if (data->args)
		ft_memdel((void **)&data->args);
	return (0);
}

void			parsecommand(t_data *data, t_liste *liste)
{
	int			nb_pipe;
	t_liste2	*dest;

	(void)liste;
	data->l = nsplit_on_inib(data->line);
	if ((nb_pipe = search_nb_pipe(data->l) + 1) > 512)
	{
		free_all(data, NULL);
		return (ft_putendl_fd("sh : over pipe limit", 2));
	}
	dest = (t_liste2 *)malloc(sizeof(t_liste2));
	data->liste = final_list(dest, data->l, nb_pipe);
	if (data->liste->tabb[0] && design_norm(data))
		return ;
	built_or_launch(data);
}
