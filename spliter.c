/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 13:24:40 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/04 17:20:28 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int				is_a_spec(char c)
{
	if ((c == '>' || c == '<' || c == '|' ||
		c == ';' || c == '&' || c == '|' ||
		c == '`'))
		return (1);
	return (0);
}

int				sub_split_on_spec(char **cmd)
{
	// if ((**cmd == '>' || **cmd == '<') && (*cmd - 1) &&
		// ft_isdigit(*(*cmd - 1)) && (!*(*cmd - 2) ||
		// (*cmd - 2 && *(*cmd - 2) == ' ')))
		// return (1);
	char *tmp;

	tmp = *cmd;
	if ((**cmd == '>' || **cmd == '<') && (*cmd + 1) && *(*cmd + 1) == '&')
	{
		while (*cmd - 1 && ft_isdigit(*(*cmd - 1)))
			*cmd -= 1;
		if (*(*cmd - 1) && *(*cmd - 1) != ' ' && !(is_a_spec(**cmd - 1)))
			*cmd = tmp;
	}
	return (0);
}

t_token			*analyse_and_stock(char **ptr, char **cmd, t_token **base)
{
	t_token		*token;
	t_token		*maillon;

	if (!ptr || !*ptr || !**ptr)
		return (*base);
	if (is_a_spec(**cmd))
		return (split_on_sp(ptr, cmd, base, NULL));
	**cmd = 0;
	if (!(maillon = (t_token *)malloc(sizeof(t_token))))
		return (0);
	maillon->arg = replace_rest_of_space(ft_strdup(*ptr), ft_strlen(*ptr));
	maillon->inib = 0;
	if ((*ptr = *(cmd)))
		*ptr = *cmd + 1;
	**cmd = ' ';
	maillon->token = OTHER;
	maillon->next = NULL;
	if (!base || !*base)
		return (maillon);
	token = *base;
	while (token->next)
		token = token->next;
	token->next = maillon;
	return (*base);
}

t_token			*to_list(char *cmd, int i)
{
	t_token		*tmp;
	t_token		*token;

	token = NULL;
	if (!cmd || !*cmd)
		return (0);
	while (cmd[++i] && cmd[i] == ' ')
		;
	if (!cmd[i])
		return (0);
	cmd = free_space(cmd, 0, 0, -1);
	token = ft_find_space(cmd, token, 0, 0);
	tmp = token;
	while (token)
		token = token->next;
	token = tmp;
	return (token);
}
