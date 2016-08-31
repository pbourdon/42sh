/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allwrites.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 18:20:47 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/23 17:28:03 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		writeonwhile(void)
{
	ft_putstr("minishell $> ");
}

void		errorbinary(t_data *data, char *str)
{
	if (str)
		free(str);
	ft_putstr("zsh: command not found: ");
	ft_putendl(data->args[0]);
}

t_liste2	*createliste(void)
{
	t_liste2	*liste;

	liste = (t_liste2 *)malloc(sizeof(t_liste2));
	liste->next = NULL;
	return (liste);
}
