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

int				switch_case(t_token *ptr, int nb_redir)
{
	if (ptr->token == 3 && ft_strncmp(ptr->arg, "|", 1) != 0 && ptr->next == NULL)
	{
		ft_putendl("Missing name for redirect.");
		return (-1);
	}
	else if ((nb_redir > 1 && ptr->next != NULL) || (nb_redir > 1 && ft_strncmp(ptr->arg, "|", 1) == 0 && ptr->next == NULL))
	{
		ft_putendl("Ambigous output redirect.");
		return (-1);
	}
	else if (ptr->token == 3 && ft_strncmp(ptr->arg, "|", 1) == 0 && ptr->next == NULL)
	{
		ft_putendl("Invalid null command.");
		return (-1);
	}
	return (0);
}

int				set_redir_var(char *str, int token, int nb_redir)
{
	if (ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, ">", 1) == 0 || token == 1)
		nb_redir++;
	else if (ft_strncmp(str, "|", 1) == 0 && nb_redir > 0)
		nb_redir++;
	else if (token > 3 || (ft_strncmp(str, "|", 1) == 0 && nb_redir == 0))
		nb_redir = 0;
	return (nb_redir);
}

int				check_aggr(char *str, int token)
{
	printf("teest: %d\n", ft_isdigit(str[2]));
	if (token == 1)
	{
		if (ft_strlen(str) < 3 || (ft_strlen(str) == 3 && ft_isdigit(str[2]) == 0))
		{
			ft_putendl("syntax error near unexpected token `newline'");
			return (-1);
		}
	}
	return (0);
}

int				check_list(t_token *liste, t_token *ptr)
{
	int			nb_redir;
	int			under_cmd;
	int			ret;

	under_cmd = 0;
	nb_redir = 0;
	ret = 0;
	ptr = liste;
	while (ptr != NULL)
	{
		nb_redir = set_redir_var(ptr->arg, ptr->token, nb_redir);
		if ((ret = check_aggr(ptr->arg, ptr->token)) == -1)
			return (-1);
		if ((ret = switch_case(ptr, nb_redir)) == -1)
			return (-1);
		ptr = ptr->next;
	}
	return (0);
}