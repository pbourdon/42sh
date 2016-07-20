/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 18:14:12 by bde-maze          #+#    #+#             */
/*   Updated: 2016/07/20 18:14:13 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			check_list(t_token *liste)
{
	t_token		*ptr;
	int			i;

	i = 0;
	ptr = liste;
	while (ptr->next != NULL)
	{
		while (ptr->arg[i])

	}
}