/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_on_spec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 13:24:32 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/20 18:18:25 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_tk		*add_end_list(t_tk *tk, t_tk **base)
{
	t_tk *tmp;

	if (!base || !*base)
		return (tk);
	tmp = *base;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = tk;
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

void			sub_split_norm(char **cmd, t_tk *cur, int i)
{
	char *tmp;

	if (ft_isdigit(**cmd))
	{
		*cmd += 1;
		while (*cmd && **cmd && ft_isdigit(**cmd))
		{
			cur->arg[++i] = **cmd;
			*cmd += 1;
		}
	}
	if (!ft_strncmp(*cmd, ">&", 2))
	{
		if (ft_isdigit(cur->arg[0]))
			cur->arg[++i] = '>';
		cur->arg[++i] = '&';
		*cmd += 2;
	}
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
		ft_putstr("ici: ");
		ft_putendl(*cmd);
	}
	cur->arg[++i] = 0;
	*cmd -= 1;
}

t_tk		*split_norm(char **ptr, char **cmd, t_tk **base, t_tk *cur)
{
	int		i;

	i = 0;
	if (ft_isdigit(**cmd) || !ft_strncmp(*cmd, ">&", 2))
		sub_split_norm(cmd, cur, i);
	else if ((**cmd == '&' || **cmd == '>' || **cmd == '<')
		&& *(*cmd + 1) == cur->arg[i])
	{
		cur->arg[++i] = *(*cmd + 1);
		*cmd += 1;
	}
	cur->tk = add_token(cur->arg);
	*base = add_end_list(cur, base);
	while (*cmd && *(*cmd + 1) && *(*cmd + 1) == ' ')
		*cmd += 1;
	*ptr = *cmd;
	return (*base);
}

t_tk		*split_on(char **ptr, char **cmd, t_tk **base, t_tk *cur)
{
	char	c;
	int		len;

	len = ft_strlen(*ptr);
	sub_split_on_spec(cmd, ptr);
	c = **cmd;
//	ft_putstr("c is ");
//	ft_putchar(c);
//	ft_putendl(*cmd - 1);
	if (!(cur = (t_tk *)malloc(sizeof(t_tk))))
		return (0);
	cur->next = NULL;
	cur->inib = 0;
	if (*ptr != *cmd)
	{
		**cmd = 0;
		cur->arg = replace_rest_of_space(ft_strdup(*ptr), ft_strlen(*ptr));
		*base = add_end_list(cur, base);
		**cmd = c;
		*ptr = *cmd;
		cur->tk = OTHER;
		return (split_on(ptr, cmd, base, NULL));
	}
	if (!(cur->arg = ft_memalloc(sizeof(char) * len)))
		return (0);
	cur->arg = ft_memset(cur->arg, 0, len);
	cur->arg[0] = c;
	return (split_norm(ptr, cmd, base, cur));
}
