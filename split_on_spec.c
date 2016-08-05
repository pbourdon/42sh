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

int		add_token(char *str)
{
	int	ret;

	ret = 0;

	if (!(ft_strncmp(str, ">", 1)) || !(ft_strncmp(str, "<", 1)) || !(ft_strcmp(str, "|")))
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

t_token	*split_for_the_norm(char **ptr, char **cmd, t_token **base, t_token *cur)
{
	if ((**cmd == '&' || **cmd == '|' || **cmd == '>' || **cmd == '<')
		&& *(*cmd + 1) == cur->arg[0])
	{
		cur->arg[1] = cur->arg[0];
		*cmd += 1;
	}
	cur->token = add_token(cur->arg);
	*base = add_end_list(cur, base);
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
	if (*ptr != *cmd)
	{
		**cmd = 0;
		cur->arg = replace_rest_of_space(ft_strdup(*ptr), ft_strlen(*ptr));
		*base = add_end_list(cur, base);
		**cmd = c;
		ptr = cmd;
		cur->token = OTHER;
		return (split_on_spec(ptr, cmd, base));
	}
	if (!(cur->arg = (char *)malloc(sizeof(char) * 3)))
		return (0);
	cur->arg = ft_memset(cur->arg, 0, 3);
	cur->arg[0] = c;
	return (split_for_the_norm(ptr, cmd, base, cur));
}

int		is_a_spec(char c)
{
	if ((c == '>' || c == '<' || c == '|' ||
		 c == ';' || c == '&' || c == '|' ||
		 c == '`'))
		return (1);
	return (0);
}
