/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 13:24:40 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/18 17:59:11 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int				is_a_spec(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == ';')
		return (1);
	return (0);
}

int				is_a_spec2(char *str, char c)
{
	int			i;

	i = is_a_spec(c);
	if (i == 1)
		return (1);
	else if (ft_strncmp(str, "&&", 2) == 0)
		return (1);
	return (0);
}

int				sub_split_on_spec(char **cmd, char **ptr)
{
	char		*tmp;

	tmp = *cmd;
	if (!ft_strncmp(*cmd, ">&", 2) || !ft_strncmp(*cmd, "<&", 2))
	{
		while (*cmd - 1 && ft_isdigit(*(*cmd - 1)))
			*cmd -= 1;
		if (*cmd != *ptr && *cmd - 1 && *(*cmd - 1) > 0 && *(*cmd - 1) != ' '
			&& !(is_a_spec2(*cmd, *(*cmd - 1))))
			*cmd = tmp;
	}
	return (0);
}

t_tk			*analyse_and_stock(char **ptr, char **cmd, t_tk **base)
{
	t_tk		*tk;
	t_tk		*maillon;

	if (!ptr || !*ptr || !**ptr)
		return (*base);
	if (is_a_spec2(*cmd, **cmd))
		return (split_on(ptr, cmd, base, NULL));
	**cmd = 0;
	if (!(maillon = (t_tk *)malloc(sizeof(t_tk))))
		return (0);
	maillon->arg = replace_rest_of_space(ft_strdup(*ptr), ft_strlen(*ptr));
	maillon->inib = 0;
	if ((*ptr = *(cmd)))
		*ptr = *cmd + 1;
	**cmd = ' ';
	maillon->tk = OTHER;
	maillon->next = NULL;
	if (!base || !*base)
		return (maillon);
	tk = *base;
	while (tk->next)
		tk = tk->next;
	tk->next = maillon;
	return (*base);
}

t_tk			*to_list(char *cmd, int i)
{
	t_tk		*tmp;
	t_tk		*tk;

	tk = NULL;
	if (!cmd || !*cmd)
		return (0);
	while (cmd[++i] && cmd[i] == ' ')
		;
	if (!cmd[i])
		return (0);
	cmd = free_space(cmd, 0, 0, -1);
	tk = find_space(cmd, tk, 0, 0);
	tmp = tk;
	while (tk)
		tk = tk->next;
	tk = tmp;
	return (tk);
}
