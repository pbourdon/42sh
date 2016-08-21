/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_arg_to_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 17:01:40 by cmichaud          #+#    #+#             */
/*   Updated: 2016/08/21 22:52:36 by cmichaud         ###   ########.fr       */
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

t_liste		*del_last_null_arg(t_liste *liste)
{
	t_liste *tmp;
	t_liste *t;
	t_liste *b;

	tmp = liste;
	b = liste;
	while (liste)
	{
		if (liste->next && !liste->next->arg)
		{
			tmp = liste->next;
			liste->next = NULL;
			while (tmp)
			{
				t = tmp->next;
				if (tmp->arg)
					free(tmp->arg);
				free(tmp);
				tmp = t;
			}
		}
		liste = liste->next;
	}
	return (b);
}

char		*ft_str_f_join(char *b, char *d)
{
	char *tmp;

	if (!b && !d)
		return (NULL);
	if (!b && d)
		return (ft_strdup(d));
	if (!d)
		return (b);
	tmp = b;
	b = ft_strjoin(b, " ");
	free(tmp);
	tmp = b;
	b = ft_strjoin(b, d);
	free(tmp);
	tmp = NULL;
	return (b);
}

char		*get_arg_nodes(t_tree *tree)
{
	char	*str;

	str = NULL;
	while (tree)
	{
		if (tree->left)
			str = ft_str_f_join(str, get_arg_nodes(tree->left));
		str = ft_str_f_join(str, tree->arg);
		tree = tree->right;
	}
	return (str);
}

void		arg_to_list(t_liste *liste, t_tree *tree)
{
	t_liste *cur;

	cur = liste;
	while (tree && tree->token > 3)
	{
		ft_putstr("while arg\n");
		if (tree->left)
		{
			if (cur->arg != NULL)
			{
				cur->next = create_list();
				cur = cur->next;
			}
			cur->arg = get_arg_nodes(tree->left);
		}
		cur->next = create_list();
		cur = cur->next;
		cur->arg = ft_strdup(tree->arg);
		tree = tree->right;
	}
	if (tree)
	{
		if (cur->arg != NULL)
		{
			cur->next = create_list();
			cur = cur->next;
		}
		cur->arg = get_arg_nodes(tree);
	}
}
