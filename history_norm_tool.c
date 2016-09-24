/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_norm_tool.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 23:40:15 by cmichaud          #+#    #+#             */
/*   Updated: 2016/09/21 23:40:38 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

t_history		*hist_stock(char *line, t_history *n,
							t_history *p, t_history *history)
{
	history->str = ft_strdup(line);
	history->prev = p;
	history->next = n;
	return (history);
}
