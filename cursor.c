/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 16:02:48 by bde-maze          #+#    #+#             */
/*   Updated: 2016/10/14 23:47:54 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	cursor_init(void)
{
	g_cursor.position_x_abs = 1;
	g_cursor.position_y_abs = tgetnum("li") - 1;
	g_cursor.position_x_rel = 6;
	g_cursor.position_y_rel = 0;
	g_cursor.position_line = 0;
}
