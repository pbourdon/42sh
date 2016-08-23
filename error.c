/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 18:14:12 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/16 16:46:55 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int				set_redir_var(char *str, int nb_redir)
{
	if (ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, "<<", 2) == 0)
		nb_redir++;
	return (nb_redir);
}

int				set_redir_var2(char *str, int nb_redir2)
{
	if (ft_strncmp(str, ">", 1) == 0 || ft_strncmp(str, ">>", 2) == 0)
		nb_redir2--;
	return (nb_redir2);
}

int				check_aggr(char *str, int tk)
{
	if (tk == 1)
	{
		if (ft_strlen(str) < 3 || (ft_strlen(str) == 3 &&
		(ft_isdigit(str[2]) == 0 && str[2] != '-')))
		{
			ft_putendl("syntax error near unexpected tk `newline'");
			return (-1);
		}
		else if (ft_strlen(str) == 4 &&
			(ft_isdigit(str[3]) == 0 && str[3] != '-'))
		{
			ft_putchar(str[3]);
			ft_putendl(": ambigous redirect");
			return (-1);
		}
	}
	return (0);
}

void			add_digit_aggr(t_tk *liste)
{
	char		*tmp;

	tmp = ft_strdup("1");
	while (liste != NULL)
	{
		if (liste->tk == 1 && ft_isdigit(liste->arg[0]) == 0)
		{
			tmp = ft_strjoin(tmp, liste->arg);
			liste->arg = ft_strdup(tmp);
		}
		liste = liste->next;
	}
}

int				check_list(t_tk *liste, t_tk *ptr, int ret, int nb_agg)
{
	int			nb_redir;
	int			nb_redir2;
	int			under_cmd;

	under_cmd = 0;
	nb_redir = 0;
	nb_redir2 = 0;
	ptr = liste;
	while (ptr != NULL)
	{
		if (ptr->tk == 1)
			nb_agg++;
		nb_redir = set_redir_var(ptr->arg, nb_redir);
		nb_redir2 = set_redir_var(ptr->arg, nb_redir2);
		if ((ret = check_aggr(ptr->arg, ptr->tk)) == -1)
			return (-1);
		if ((ret = switch_case(ptr, nb_redir, nb_redir2)) == -1)
			return (-1);
		ptr = ptr->next;
	}
	add_digit_aggr(liste);
	return (0);
}
