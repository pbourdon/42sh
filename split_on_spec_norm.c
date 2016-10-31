/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_on_spec_norm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 18:47:15 by cmichaud          #+#    #+#             */
/*   Updated: 2016/09/22 18:48:36 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	sub_sub_split_norm(char **cmd, t_tk *cur, int i)
{
	char		*tmp;

	tmp = *cmd;
	while (*cmd && ft_isdigit(**cmd))
	{
		cur->arg[++i] = **cmd;
		*cmd += 1;
	}
	if (*(*cmd) && (*(*cmd)) == '-')
	{
		cur->arg[++i] = *(*cmd);
		*cmd += 1;
	}
	if (!is_a_spec2(*cmd, **cmd) && **cmd != ' ' && **cmd != 0)
	{
		*cmd = tmp;
		tmp = ft_strchr(cur->arg, '&');
		*(tmp + 1) = 0;
	}
	cur->arg[++i] = 0;
	*cmd -= 1;
}

void	sub_split_norm_norm(char **cmd, t_tk *cur, int i)
{
	if (!ft_strncmp(*cmd, ">&", 2))
	{
		if (ft_isdigit(cur->arg[0]))
			cur->arg[++i] = '>';
		cur->arg[++i] = '&';
		*cmd += 2;
	}
	else if (!ft_strncmp(*cmd, "<&", 2))
	{
		if (ft_isdigit(cur->arg[0]))
			cur->arg[++i] = '<';
		cur->arg[++i] = '&';
		*cmd += 2;
	}
	sub_sub_split_norm(cmd, cur, i);
}
