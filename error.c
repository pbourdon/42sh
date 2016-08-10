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

// int				edit_error_message(t_token *ptr, char *prev, int tworeddir)
// {
	// if (tworeddir == 1)
		// ft_putendl("Ambigous output redirect.");
	// else if (!ft_strncmp(ptr->arg, "<", 1) || !ft_strncmp(prev, "<", 1) ||
		// !ft_strncmp(ptr->arg, ">", 1) || !ft_strncmp(prev, ">", 1))
		// ft_putendl("Missing name for redirect.");
	// else
		// ft_putendl("Invalid null command.");
	// return (-1);
// }
// 
// int				check_loop(t_token *ptr, char *prev_arg)
// {
	// int			prev;
// 
	// prev = 0;
	// if (ptr->token != 0)
	// {
		// if (prev == 1)
			// return (edit_error_message(ptr, prev_arg, 0));
		// prev = 1;
	// }
	// else
		// prev = 0;
	// return (prev);
// }
// 
// int				multi_reddir(t_token *ptr, int tworeddir)
// {
	// if (ptr->token != 3 && ptr->token > 3)
		// tworeddir = 0;
	// else if ((ft_strcmp(ptr->arg, "<") == 0 || ft_strcmp(ptr->arg, ">") == 0) &&
		// tworeddir == 1)
		// return (-1);
	// else if ((ft_strcmp(ptr->arg, "<") == 0 || ft_strcmp(ptr->arg, ">") == 0) &&
		// tworeddir == 0)
		// tworeddir = 1;
	// return (tworeddir);
// }

void			switch_case(t_token *ptr, int nb_redir)
{
	if (ptr->token == 3 && ft_strncmp(ptr->arg, "|", 1) != 0 && ptr->next == NULL)
		ft_putendl("Missing name for redirect.");
	else if ((nb_redir > 1 && ptr->next != NULL) || (nb_redir > 1 && ft_strncmp(ptr->arg, "|", 1) == 0 && ptr->next == NULL))
		ft_putendl("Ambigous output redirect.");
	else if (ptr->token == 3 && ft_strncmp(ptr->arg, "|", 1) == 0 && ptr->next == NULL) 
		ft_putendl("Invalid null command.");
}

int				set_redir_var(char *str, int token, int nb_redir)
{
	if (ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, ">", 1) == 0)
		nb_redir++;
	else if (ft_strncmp(str, "|", 1) == 0 && nb_redir > 0)
		nb_redir++;
	else if (token > 3 || (ft_strncmp(str, "|", 1) == 0 && nb_redir == 0))
		nb_redir = 0;
	return (nb_redir);
}

int				check_list(t_token *liste, t_token *ptr)
{
	int			nb_redir;
	int			under_cmd;

	under_cmd = 0;
	nb_redir = 0;
	ptr = liste;
	while (ptr != NULL)
	{
		nb_redir = set_redir_var(ptr->arg, ptr->token, nb_redir);
		switch_case(ptr, nb_redir);
		ptr = ptr->next;
	}
	return (0);
	// char		*prev_arg;
	// int			ret;
// 
	// (void)tworeddir;
	// ret = 0;
	// ptr = liste;
	// prev_arg = NULL;
	// while (ptr != NULL)
	// {
		// if ((tworeddir = multi_reddir(ptr, tworeddir)) == -1)
			// return (edit_error_message(ptr, prev_arg, tworeddir));
		// ret = check_loop(ptr, prev_arg);
		// prev_arg = ft_strdup(ptr->arg);
		// ptr = ptr->next;
	// }
	// if (!ptr)
		// return (0);
	// if (ret == -1)
		// return (-1);
	// if (ptr->token != 0)
	// {
		// if (ret == 1)
			// return (edit_error_message(ptr, prev_arg, 0));
	// }
}
