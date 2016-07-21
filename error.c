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

#include "includes/minishell.h"

int			edit_error_message(t_token *ptr, char *prev)
{
	ft_putstr("prev: ");
	ft_putendl(prev);
	ft_putstr("ptr->arg: ");
	ft_putendl(ptr->arg);
	if (!ft_strncmp(ptr->arg, "<", 1) || !ft_strncmp(prev, "<", 1) ||
		!ft_strncmp(ptr->arg, ">", 1) || !ft_strncmp(prev, ">", 1))
		ft_putendl("Missing name for redirect.");
	else
		ft_putendl("Invalid null command.");
	return (-1);
}

int			check_loop(t_token *ptr, char *prev_arg)
{
	int			prev;

	prev = 0;
	if (ptr->token != 0)
	{
		if (prev == 1)
			return (edit_error_message(ptr, prev_arg));
		prev = 1;
	}
	else
		prev = 0;
	return (prev);
}

int			check_list(t_token *liste)
{
	t_token		*ptr;
	char		*prev_arg;
	int			i;
	int			ret;

	i = 0;
	ret = 0;
	ptr = liste;
	prev_arg = NULL;
	while (ptr->next != NULL)
	{
		ret = check_loop(ptr, prev_arg);
		prev_arg = ft_strdup(ptr->arg);
		ptr = ptr->next;
	}
	if (ret == -1)
		return (-1);
	if (ptr->token != 0)
	{
		if (ret == 1)
			return (edit_error_message(ptr, prev_arg));
	}
	return (0);
}