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

char		*erase_first_space(char *line)
{
	int			i;

	i = 0;
	while ((line[i] == ' ') || (line[i] == 9))
		line++;
	i = 0;
	while (line[i])
	{
		if (line[i] == 9)
			line[i] = ' ';
		i++;
	}
	return (line);
}

char		*replace_rest_of_space(char *str, int len)
{
	int i;
	i = len;
	while (str[len - 1] && str[len - 1] == ' ')
		--len;
	if (i != len)
	{
		if (str[len - 1] == '\\')
		{
			if (str[len - 2] && str[len - 2] == '\\')
				str[len] = 0;
			else if (str[len + 1])
				str[len + 1] = 0;
			return (str);
		}
		else
			str[len] = 0;
		return (str);
	}
	return (str);
}

t_token		*analyse_and_stock(char **ptr, char **cmd, t_token **base)
{
	t_token *token;
	t_token *maillon;
	if (!ptr || !*ptr || !**ptr)
		return (*base);
	if (is_a_spec(**cmd))
		return (split_on_spec(ptr, cmd, base));
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

t_token		*ft_find_space(char *cmd, t_token *token)
{
	char	*ptr;
	char	*tmp;
	char	quote;
	int		inib;

	ptr = cmd;
	quote = 0;
	inib = 0;
	tmp = cmd;
	while (cmd && *cmd)
	{
		if ((!(quote + inib) || (!(inib) && quote == '\'')) && is_a_spec(*cmd))
		{
			token = analyse_and_stock(&ptr, &cmd, &token);
			ptr = cmd;
			if ((*cmd && cmd && is_a_spec(*cmd)) || (*cmd == ' '))
			{
				++ptr;
			}
		}
		if (quote && *cmd == quote && inib == 0)
			quote = 0;
		else if (!quote && (*cmd == '"' || *cmd == '\''))
			quote = *cmd;
		else if (*cmd == '\\' && quote + inib == 0)
			inib = 1;
		else
			inib = 0;
		cmd++;
	}
	if (ptr != cmd)
		token = analyse_and_stock(&ptr, &cmd, &token);
	return (token);
}

char		*free_space(char *str, int quote, int d, int i)
{
	int inib;

	inib = 0;
	while (str[++i])
	{
		if (!quote && str[i] == ' ' && inib == 0)
		{
			if (i != 0)
				str[d++] = str[i];
			while (str[++i] && str[i] == ' ')
				;
		}
		if (quote && str[i] == quote && inib == 0)
			quote = 0;
		else if (!quote && (str[i] == '"' || str[i] == '\''))
			quote = str[i];
		if (inib == 1)
			inib = 0;
		else if (str[i] == '\\' && quote == 0)
            inib = 1;
		str[d++] = str[i];
	}
	str[d] = '\0';
	return (replace_rest_of_space(str, ft_strlen(str)));
}

t_token		*to_list(char *cmd, int i)
{
	t_token	*tmp;
	t_token	*token;

	token = NULL;
	if (!cmd || !*cmd)
		return (0);
	while (cmd[++i] && cmd[i] == ' ')
		;
	if (!cmd[i])
		return (0);
	cmd = free_space(cmd, 0, 0, -1);
	token = ft_find_space(cmd, token);
	tmp = token;
	while (token)
		token = token->next;
	token = tmp;
	return (token);
}
