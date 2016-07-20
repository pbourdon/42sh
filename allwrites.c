/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allwrites.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 18:20:47 by hlouar            #+#    #+#             */
/*   Updated: 2016/05/19 17:20:05 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	writeonwhile(void)
{
	ft_putstr("minishell $> ");
}

void	errorbinary(t_data *data, char *str)
{
	free(str);
	ft_putstr("zsh: command not found: ");
	ft_putendl(data->args[0]);
}
