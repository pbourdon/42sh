/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 17:24:29 by cmichaud          #+#    #+#             */
/*   Updated: 2016/07/21 18:50:18 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tree		*fcnt(t_tree *tree, t_token *token, int prio, t_token **base)
{
	t_token *tmp;
	
	tmp = *base;
	while (tmp != token)
	{
		if (tmp->token == prio)
		{
			tree->left = set_tree(tree->left, tmp);
			if (prio > 0)
				--prio;
			fcnt(tree->left, token, prio, base);
		}
		tmp = tmp->next;
	}
	return (tree);
}

t_tree		*set_tree(t_tree *tree, t_token *token)
{
	if (!(tree = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	tree->arg = token->arg;
	tree->token = token->token;
	tree->right = NULL;
	tree->left = NULL;
	return (tree);
}

t_tree		*build_tree(t_tree *tree, t_token *token, int prio, t_token **base)
{
	if (!tree)
		tree = set_tree(tree, token);
	if (prio > 0)
		--prio;
	fcnt(tree, token, prio, base);
	return (tree);
}

t_tree		*to_tree(t_token *token, t_token **base, int prio, t_tree *tree)
{
	t_token		*tmp;

	tree = NULL;
	prio = 5;
	while (token)
	{
		if (token->token == prio)
		{
			tmp = token;
			build_tree(tree, token, prio, base);
		}
		token = token->next;
	}
	return (tree);
}
