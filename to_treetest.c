/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_treetest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 19:36:50 by cmichaud          #+#    #+#             */
/*   Updated: 2016/07/23 15:16:10 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void		aff(t_tree *tree)
{
	if (tree == NULL)
	{
		ft_putendl("End node\n");
		return ;
	}
	ft_printf("The node [%s]\n", tree->arg);
	ft_printf("TO LEFT ");
	aff(tree->left);
	ft_printf("TORIGHT ");
	aff(tree->right);
	return ;
}


t_tree		*new_node(t_token *token)
{
	t_tree *tree;

	if (!(tree = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
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
		ft_putstr("    the token == base        ");
		*save = (*token)->next;
		free(*token);
		*base = NULL;
		*token = *save;
		if (*token == NULL)
			return (0);
	}
	else if ((*save = *base))
	{
//		ft_printf("    the token != base       and base->arg is [%s] ", (*base)->arg);
//		*save = *base;
		while ((*save)->next != *token)
		{ft_putstr("l");				*save = (*save)->next;};
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
	t_token *save;
	t_token *base;

	base = token;
//	ft_printf("begin loop of recur\n");
	while (prio != -1)
	{
		token = base;
		while (token)
		{				ft_putstr("1test");

			ft_printf("LOOP = token : str = [%s] token = [%d] for prio [%d]\n", token->arg, token->token, prio);
			if (token->token == prio)
			{
				if (!str)
				{
					ft_printf("On rentre dans la merde\n");
					tree = new_node(token);
				}
				else if (!ft_strcmp(str, "left"))
					tree = ((tree->left = new_node(token)));
				else if (!ft_strcmp(str, "right"))
					tree = ((tree->right = new_node(token)));
				if (!is_base(&token, &base, &save))
					return (tree);//}				if (token == base)
					
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
					ft_printf("    the token != base       and base->arg is [%s] ", base->arg);
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
				if (base && ft_printf("\nTO THE LEFT!!!!!!!!!!!!"))
					to_tree(tree, base, (prio - 1), "left");
				if (token && ft_printf("\nTO THE RIGHT!!!!!!!!!!!!"))
					to_tree(tree, token, prio, "right");
				return (tree);
			}
			ft_putstr("2test\n");
			token = token->next;
		}
		prio--;
	}
	ft_printf("END loop of to_tree\n");
	return (tree);
}
