/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_order.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 15:23:18 by cmichaud          #+#    #+#             */
/*   Updated: 2016/07/26 14:44:26 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char		*in_out(char *str)
{
	int		i;
	int		quote;
	int		inib;

	inib = 0;
	quote = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ' && !(quote + inib))
		{
			if (str[i + 1] && str[i + 1] != ' ' && !(str[i] = 0))
				return (str + i + 1);
		}
		if (quote && str[i] == quote && inib == 0)
			quote = 0;
		else if (!quote && (str[i] == '"' || str[i] == '\''))
			quote = str[i];
		else if (str[i] == '\\' && quote + inib == 0)
			inib = 1;
		else
			inib = 0;
	}
	return (0);
}

t_token		*new_out(t_token **ptr, t_token **prev, t_token **base, char *tmp)
{
	t_token	*new;

	if (!(new = (t_token *)malloc(sizeof(t_token))))
		return (0);
	new->arg = ft_strdup(tmp);
	new->token = OTHER;
	if (*prev == *ptr && *prev == *base)
	{
		new->next = (*base);
		(*base) = new;
	}
	else
	{
		new->next = *ptr;
		(*prev)->next = new;
	}
	return (new);
}

void		concat_out(t_token **prev, char *str)
{
	char	*tmp;

	tmp = (*prev)->arg;
	(*prev)->arg = ft_strjoin((*prev)->arg, " ");
	ft_memdel((void *)&tmp);
	tmp = (*prev)->arg;
	(*prev)->arg = ft_strjoin((*prev)->arg, str);
	ft_memdel((void *)&tmp);
}

int 		is_a_next_exec(t_token *ptr)
{
	if (ptr->token != 0 && ptr->token != 1 && ptr->token != 2 && ptr->token != 3)
		return (1);
	else if (ptr->token == 3 && !ft_strcmp("|", ptr->arg))
		return (1);
	return (0);
}

t_token		*good_order(t_token *ptr, t_token *prev, t_token *base)
{
	char	*tmp;
	t_token	*in;

	in = NULL;
	while (ptr)
	{
		if (((ptr->token == REDDIR && ft_strcmp(ptr->arg, "|")) ||
			 ptr->token == AGGR)
			&& ptr->next && ptr->next->token == 0
			&& (tmp = in_out(ptr->next->arg)))
		{
			if (prev == ptr || prev->token != 0)
				in = new_out(&ptr, &prev, &base, tmp);
			else
				concat_out(&in, tmp);
		}
		else if (!in && ptr->token == 0)
			in = ptr;
		if (is_a_next_exec(ptr))
			in = NULL;
		prev = ptr;
		ptr = ptr->next;
	}
	return (base);
}
