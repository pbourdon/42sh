/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_on_spec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 13:24:32 by bde-maze          #+#    #+#             */
/*   Updated: 2016/07/23 13:53:26 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_token		*add_end_list(t_token *token, t_token **base)
{
	t_token *tmp;

	if (!base || !*base)
		return (token);
	tmp = *base;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = token;
	return (*base);
}

int			add_token(char *str)
{
	int		ret;

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

void			sub_split_norm(char **cmd, t_token *cur, int i)
{
	if (ft_isdigit(**cmd))
	{
		while (*cmd + 1 && *(*cmd + 1) && ft_isdigit(*(*cmd + 1)))
		{
			cur->arg[++i] = *(*cmd + 1);
			*cmd += 1;
		}
		*cmd += 1;
	}
	if (!ft_strncmp(*cmd, ">&", 2) || !ft_strncmp(*cmd, "<&", 2))
	{
		if (ft_isdigit(*(*cmd - 1)))
			**cmd == '>' ? (cur->arg[++i] = '>') : (cur->arg[++i] = '<');
		cur->arg[++i] = '&';
		*cmd += 1;
	}
	while (*cmd + 1 && *(*cmd + 1))
	{
		cur->arg[++i] = *(*cmd + 1);
		*cmd += 1;
	}
	if (*(*cmd + 1) && (*(*cmd + 1)) == '-')
	{
		cur->arg[++i] = *(*cmd + 1);
		*cmd += 1;
	}
	*cmd += 1;
}

t_token		*split_norm(char **ptr, char **cmd, t_token **base, t_token *cur)
{
	int		i;

	i = 0;
	if ((ft_isdigit(**cmd)) || (((**cmd == '<' || **cmd == '>') && ((*cmd + 1) && (*(*cmd + 1)) == '&'))))
		sub_split_norm(cmd, cur, i);
	else if ((**cmd == '&' || **cmd == '|' || **cmd == '>' || **cmd == '<')
		&& *(*cmd + 1) == cur->arg[i])
	{
		cur->arg[++i] = *(*cmd + 1);
		*cmd += 1;
	}
	cur->token = add_token(cur->arg);
	*base = add_end_list(cur, base);
	while (*cmd && *(*cmd + 1) && *(*cmd + 1) == ' ')
		*cmd += 1;
	*ptr = *cmd;
	return (*base);
}

t_token		*split_on_sp(char **ptr, char **cmd, t_token **base, t_token *cur)
{
	char	c;
	int		len;

	len = ft_strlen(*ptr);
	sub_split_on_spec(cmd);
	c = **cmd;
	if (!(cur = (t_token *)malloc(sizeof(t_token))))
		return (0);
	cur->next = NULL;
	cur->inib = 0;

	if (*ptr != *cmd)
	{
		**cmd = 0;
		cur->arg = replace_rest_of_space(ft_strdup(*ptr), ft_strlen(*ptr));
		*base = add_end_list(cur, base);
		**cmd = c;
		ptr = cmd;
		cur->token = OTHER;
		return (split_on_sp(ptr, cmd, base, NULL));
	}
	if (!(cur->arg = ft_memalloc(sizeof(char) * len)))
		return (0);
	cur->arg = ft_memset(cur->arg, 0, 4);
	cur->arg[0] = c;
	return (split_norm(ptr, cmd, base, cur));
}
