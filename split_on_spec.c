/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_on_spec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 13:24:32 by bde-maze          #+#    #+#             */
/*   Updated: 2016/07/20 13:24:33 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_token	*add_end_list(t_token *token, t_token **base)
{
	t_token *tmp;

	if (!base || !*base)
		return (token);
	tmp = *base;
//	ft_putstr("seg add");
	while (tmp->next)
	{
		tmp = tmp->next;
//		ft_putstr("seg add1");
	}
	tmp->next = token;
//	ft_putstr("seg add1");
	return (*base);
}

int		add_token(char *str)
{
	int	ret;

	ret = 0;

	if (!(ft_strncmp(str, ">", 1)) || !(ft_strncmp(str, "<", 1)) || !(ft_strcmp(str, "|")))
	{
		ret = REDDIR;
		ft_putendl("hello_world");
	}
	return (ret);
}

t_token	*split_for_the_norm(char **ptr, char **cmd, t_token **base, t_token *cur)
{
//	ft_putstr("\n\n3llllllll");
	if ((**cmd == '&' || **cmd == '|' || **cmd == '>' || **cmd == '<')
		&& *(*cmd + 1) == cur->arg[0])
	{
		cur->arg[1] = cur->arg[0];
		*cmd += 1;
	}
	cur->token = add_token(cur->arg);
//	ft_putstr("\n\n2llllllll");
	*base = add_end_list(cur, base);
//	ft_putstr("\n\n1llllllll");
	while (*cmd && *(*cmd + 1) && *(*cmd + 1) == ' ')
		*cmd += 1;
	*ptr = *cmd;
	return (*base);
}


t_token	*split_on_spec(char **ptr, char **cmd, t_token **base)
{
	char	c;
	t_token *cur;

	c = **cmd;
	if (!(cur = (t_token *)malloc(sizeof(t_token))))
		return (0);
	cur->next = NULL;
	cur->inib = 0;
	if (*ptr != *cmd)									// other !
	{
		**cmd = 0;
		cur->arg = ft_strdup(*ptr);
		*base = add_end_list(cur, base);
		**cmd = c;
		ptr = cmd;
		cur->token = OTHER;
		return (split_on_spec(ptr, cmd, base));
	}
	if (!(cur->arg = (char *)malloc(sizeof(char) * 3))) // special !
		return (0);
	cur->arg = ft_memset(cur->arg, 0, 3);
	cur->arg[0] = c;
	return (split_for_the_norm(ptr, cmd, base, cur));
}
/*	if (!(cur->next->arg = (char *)malloc(sizeof(char) * 3)))
	{
		cur->next->arg[0] = c;
		if (*cmd + 1 && *(*cmd + 1) == c && (c == '&' || c == '|'))
			cur->next->arg[1] = c;
		else
			cur->next->arg[1] = c;
		cur->next->arg[2] = 0;
	}
	if ((*ptr = *cmd))
	{
		if (*cmd + 1 && *(*cmd + 1) == c)
			*ptr = *cmd + 2;
		else
			*ptr = *cmd + 1;
	}
	return (*base);
	}*/

int		is_a_spec(char c)
{
	if ((c == '>' || c == '<' || c == '|' ||
		 c == ';' || c == '&' || c == '|' ||
		 c == '`'))
		return (1);
	return (0);
}