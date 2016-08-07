/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 15:57:39 by bde-maze          #+#    #+#             */
/*   Updated: 2016/07/26 15:57:41 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_liste		*create_list(void)
{
	t_liste *liste;

	if (!(liste = ft_memalloc(sizeof(t_liste))))
		return (NULL);
	liste->next = NULL;
	liste->arg = NULL;
	return (liste);
}

t_liste		*fill_to_list(t_liste *liste, t_tree *tree)
{
	char	buff[ft_strlen(tree->arg) + 1];
	char	*tmp;

	buff[0] = ' ';
	while (liste->next)
		liste = liste->next;
	if (tree->left)
		liste = fill_to_list(liste, tree->left);
	if (!liste->arg)
		liste->arg = ft_strdup(tree->arg);
	else
	{
		ft_strcpy(buff + 1, tree->arg);
		tmp = ft_strjoin(liste->arg, buff);
		free(liste->arg);
		liste->arg = tmp;
	}
	if (tree->right)
		liste = fill_to_list(liste, tree->right);
	return (liste);
}

void		arg_to_list(t_liste *liste, t_tree *tree, int i)
{
	t_liste *ptr;

	if (liste == NULL)
		return ;
	ptr = liste;
	if (tree->token > 3)
	{
		if (tree->left != NULL)
			arg_to_list(ptr, tree->left, 0);
		if (tree->right != NULL)
			arg_to_list(ptr, tree->right, 0);
	}
	if (tree->token < 4)
	{
		i++;
		ptr = fill_to_list(ptr, tree);
	}
	if (i != 0)
	{
		ptr->next = ft_memalloc(sizeof(t_liste));
		ptr = ptr->next;
		ptr->arg = NULL;
		ptr->next = NULL;
	}
}
