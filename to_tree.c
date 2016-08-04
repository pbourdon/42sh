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
	ft_putstr_fd("new_node\n", 2);
	t_tree *tree;

	if (!(tree = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	ft_putstr_fd(token->arg, 2);
	ft_putstr_fd("\n", 2);
	tree->arg = token->arg;
	tree->token = token->token;
	tree->right = NULL;
	tree->left = NULL;
	return (tree);
}

int		is_base(t_token **token, t_token **base, t_token **save)
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
//		*save = *base;
		while ((*save)->next != *token)
		{
							*save = (*save)->next;};
		*token = (*token)->next;
		if (*base == *save)
		{
//			free((*base)->next);
//			(*base)->next = NULL;
			ft_memdel((void *)(&(*base)->next));

		}
		else
		{
			ft_memdel((void *)&(*save)->next);
//			free((*save)->next);
//			(*save)->next = NULL;
		}
	}
	return (1);
}

t_tree	*to_tree(t_tree *tree, t_token *token, int prio, const char *str)
{
	ft_putstr_fd("to_tree\n", 2);
	t_token *save;
	t_token *base;

	base = token;
	while (prio != -1)
	{
		token = base;
		while (token)
		{
			if (token->token == prio)
			{
				if (!str)
				{
					tree = new_node(token);
				}
				else if (!ft_strcmp(str, "left"))
					tree = ((tree->left = new_node(token)));
				else if (!ft_strcmp(str, "right"))
					tree = ((tree->right = new_node(token)));
				if (!is_base(&token, &base, &save))
				{
					ft_putstr_fd("to_tree ends\n", 2);
					return (tree);
				}//}				if (token == base)

/*				{
					ft_putstr("    the token == base        ");
					save = token->next;
					free(token);
					base = NULL;
					token = save;
					if (token == NULL)
						return (tree);
				}
				else
				{
					save = base;
					while (save->next != token)
					{ft_putstr("l");				save = save->next;};
					token = token->next;
					if (base == save)
					{
						free(base->next);
						base->next = NULL;

					}
					else
					{
						free(save->next);
						save->next = NULL;
					}
				}
*///				ft_putstr("1");
//				token = token->next;
				if (base)
					to_tree(tree, base, (prio - 1), "left");
				if (token)
					to_tree(tree, token, prio, "right");
				ft_putstr_fd("to_tree ends\n", 2);
				return (tree);
			}
			// ft_putstr("2test\n");
			token = token->next;
		}
		prio--;
	}
	return (tree);
}
