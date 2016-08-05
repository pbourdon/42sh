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

int			edit_error_message(t_token *ptr, char *prev, int tworeddir)
{
	if (tworeddir == 1)
		ft_putendl("Ambigous output redirect.");
	else if (!ft_strncmp(ptr->arg, "<", 1) || !ft_strncmp(prev, "<", 1) ||
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
			return (edit_error_message(ptr, prev_arg, 0));
		prev = 1;
	}
	else
		prev = 0;
	return (prev);
}

int			multi_reddir(t_token *ptr, int tworeddir)
{
	if (ptr->token != 3 && ptr->token > 3)
		tworeddir = 0;
	else if ((ft_strcmp(ptr->arg, "<") == 0 || ft_strcmp(ptr->arg, ">") == 0) &&
		tworeddir == 1)
		return (-1);
	else if ((ft_strcmp(ptr->arg, "<") == 0 || ft_strcmp(ptr->arg, ">") == 0) &&
		tworeddir == 0)
		tworeddir = 1;
	return (tworeddir);
}

int			check_list(t_token *liste, t_token *ptr, int tworeddir)
{
	char		*prev_arg;
	int			ret;

	ret = 0;
	ptr = liste;
	prev_arg = NULL;
	while (ptr != NULL)
	{
		if ((tworeddir = multi_reddir(ptr, tworeddir)) == -1)
			return (edit_error_message(ptr, prev_arg, tworeddir));
		ret = check_loop(ptr, prev_arg);
		prev_arg = ft_strdup(ptr->arg);
		ptr = ptr->next;
	}
	if (!ptr)
		return (0);
	if (ret == -1)
		return (-1);
	if (ptr->token != 0)
	{
		if (ret == 1)
			return (edit_error_message(ptr, prev_arg, 0));
	}
	return (0);
}
