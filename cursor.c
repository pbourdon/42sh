/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 16:02:48 by pguzman           #+#    #+#             */
/*   Updated: 2016/08/03 16:03:06 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	cursor_init(void)
{
	cursor.position_x_abs = 1;
	cursor.position_y_abs = tgetnum("li") - 1;
	cursor.position_x_rel = 1;
	cursor.position_y_rel = 0;
	cursor.position_line = 0;
}
