/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_treetest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <cmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 19:36:50 by cmichaud          #+#    #+#             */
/*   Updated: 2016/08/04 15:52:47 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void		aff(t_tree *tree)
{
	if (tree == NULL)
		return ;
	aff(tree->left);
	aff(tree->right);
	return ;
}

t_tree		*new_node(t_token *token)
{
	t_tree	*tree;

	if (!(tree = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	tree->arg = token->arg;
	tree->token = token->token;
	tree->right = NULL;
	tree->left = NULL;
	return (tree);
}

int			is_base(t_token **token, t_token **base, t_token **save)
{
	if (*token == *base)
	{
		*save = (*token)->next;
		free(*token);
		*base = NULL;
		*token = *save;
		if (*token == NULL)
			return (0);
	}
	else if ((*save = *base))
	{
		while ((*save)->next != *token)
			*save = (*save)->next;
		*token = (*token)->next;
		if (*base == *save)
			ft_memdel((void *)(&(*base)->next));
		else
			ft_memdel((void *)&(*save)->next);
	}
	return (1);
}

t_tree		*sub_to_tree(t_token *token, t_tree *tree, const char *str)
{
	if (!str)
		tree = new_node(token);
	else if (!ft_strcmp(str, "left"))
	{
		tree->left = new_node(token);
		tree = tree->left;
	}
	else if (!ft_strcmp(str, "right"))
	{
		tree->right = new_node(token);
		tree = tree->right;
	}
	return (tree);
}

t_tree		*to_tree(t_tree *tree, t_token *token, int prio, const char *str)
{
	t_token	*save;
	t_token	*base;

	base = token;
	while (prio != -1)
	{
		token = base;
		while (token)
		{
			if (token->token == prio)
			{
				tree = sub_to_tree(token, tree, str);
				if (!is_base(&token, &base, &save))
					return (tree);
				if (base)
					to_tree(tree, base, (prio - 1), "left");
				if (token)
					to_tree(tree, token, prio, "right");
				return (tree);
			}
			token = token->next;
		}
		prio--;
	}
	return (tree);
}
