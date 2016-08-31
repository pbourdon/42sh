/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/23 10:46:37 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/23 10:46:54 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int				add_token(char *str)
{
	int			ret;

	ret = 0;
	if (ft_strstr(str, ">&") != NULL || ft_strstr(str, "<&") != NULL)
		ret = AGGR;
	else if (!(ft_strncmp(str, ">", 1)) || !(ft_strncmp(str, "<", 1)) ||
	!(ft_strcmp(str, "|")))
		ret = REDDIR;
	else if (!(ft_strcmp(str, "&&")) || !(ft_strcmp(str, "||")))
		ret = OPBI;
	else if (!(ft_strcmp(str, ";")))
		ret = SEPP;
	else if (!(ft_strcmp(str, "`")))
		ret = BACK;
	return (ret);
}

t_liste			*create_list(void)
{
	t_liste		*liste;

	if (!(liste = ft_memalloc(sizeof(t_liste))))
		return (NULL);
	liste->next = NULL;
	liste->arg = NULL;
	return (liste);
}
