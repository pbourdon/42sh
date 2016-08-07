/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 16:48:13 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/07 16:48:15 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void			free_first_list(t_token *ptr)
{
	t_token		*tmp;

	while (ptr != NULL)
	{
		tmp = ptr;
		free(tmp);
		ptr = ptr->next;
	}
}
