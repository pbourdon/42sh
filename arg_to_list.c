/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 14:47:18 by cmichaud          #+#    #+#             */
/*   Updated: 2016/07/26 15:33:23 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int			calc_len(t_tree *tree, int len)
{
	if (tree->token > 3)
		if (!tree->left)
		{
			if (!tree->right)
				return (0);
			tree = tree->right;
		}
	len += ft_strlen(tree->arg);
	if (len != (len += calc_len(tree->left, len)))
		len += 1;
	if ((len += calc_len(tree->right, len)))
	len += calc_len(tree->right, len);
	
}

t_token		*arg_to_list(t_token *list, t_tree *tree, int len)
{
	t_tree *base;

	base = tree;
	while (tree)
	{
		if (tree->left && tree->left->token > 3)
			tree = tree->left;
		if (tree->left)
			calc_len(tree->left, 0);
		if (tree->right && tree->right->token > 3)
			tree = tree->right;
		if (len = calc_len(tree, 0)) // APPLIQUER LA MEME FORMULE POUR BIEN CE DEPLACER
	}
	return (list);
}
