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
	if (!(ft_strncmp(str, ">", 1)) || !(ft_strncmp(str, "<", 1)) ||
	!(ft_strcmp(str, "|")))
		ret = REDDIR;
	else if (!(ft_strcmp(str, "&&")) || !(ft_strcmp(str, "||")))
		ret = OPBI;
	else if (!(ft_strcmp(str, ";")))
		ret = SEPP;
	else if (!(ft_strcmp(str, "&")))
		ret = AGGR;
	else if (!(ft_strcmp(str, "`")))
		ret = BACK;
	return (ret);
}

int			sub_split_norm(char **cmd, t_token *cur, int i)
{
	cur->arg[++i] = *(*cmd + 1);
	*cmd += 1;
	if (cur->arg[i] == '>' && *(*cmd + 1) == '>')
	{
		cur->arg[++i] = '>';
		*cmd += 1;
	}
	else if (*(*cmd + 1) == '&')
	{
		cur->arg[++i] = '&';
		*cmd += 1;
		if (*(*cmd + 1) && ft_isdigit(*(*cmd + 1)))
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
	return (i);
}

t_token		*split_norm(char **ptr, char **cmd, t_token **base, t_token *cur)
{
	int		i;

	i = 0;
	if ((ft_isdigit(**cmd)))
		i = sub_split_norm(cmd, cur, i);
	else if (**cmd == '&' && *(*cmd + 1) == '>')
	{
		cur->arg[++i] = '>';
		*cmd += 1;
	}
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

	if (sub_split_on_spec(cmd))
		*cmd -= 1;
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
	if (!(cur->arg = (char *)malloc(sizeof(char) * 4)))
		return (0);
	cur->arg = ft_memset(cur->arg, 0, 4);
	cur->arg[0] = c;
	return (split_norm(ptr, cmd, base, cur));
}
