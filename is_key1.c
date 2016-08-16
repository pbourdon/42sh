/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_key1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 16:05:36 by pguzman           #+#    #+#             */
/*   Updated: 2016/08/04 10:15:24 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	is_delete_key(char *buffer)
{
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 51 && \
			buffer[3] == 126 && buffer[4] == 0)
		return (1);
	return (0);
}

int	is_backspace_key(char *buffer)
{
	if (buffer[0] == 127 && buffer[1] == 0 && buffer[2] == 0 && \
			buffer[3] == 0 && buffer[4] == 0)
		return (1);
	return (0);
}

int	is_direction_key(char *buffer)
{
	if (buffer[0] == 27 && buffer[1] == 91 && (buffer[2] == 66 || \
			buffer[2] == 65 || buffer[2] == 67 || buffer[2] == 68) && \
			buffer[3] == 0 && buffer[4] == 0)
		return (1);
	return (0);
}

int	is_down_key(char *buffer)
{
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66 && \
			buffer[3] == 0 && buffer[4] == 0)
		return (1);
	return (0);
}

int	is_up_key(char *buffer)
{
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65 && \
			buffer[3] == 0 && buffer[4] == 0)
		return (1);
	return (0);
}

int	is_left_key(char *buffer)
{
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 68 && \
			buffer[3] == 0 && buffer[4] == 0)
		return (1);
	return (0);
}

int	is_right_key(char *buffer)
{
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 67 && \
			buffer[3] == 0 && buffer[4] == 0)
		return (1);
	return (0);
}

int	is_enter_key(char *buffer)
{
	if (buffer[0] == 10 && buffer[1] == 0)
		return (1);
	return (0);
}

int	is_home_key(char *buffer)
{
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 72 && \
			buffer[3] == 0 && buffer[4] == 0)
		return (1);
	return (0);
}

int	is_end_key(char *buffer)
{
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 70 && \
			buffer[3] == 0 && buffer[4] == 0)
		return (1);
	return (0);
}

int	is_printable_char(char *buffer)
{
	if ((buffer[0] > 31 && buffer[0] < 127) && buffer[1] == 0)
	{
		return (1);
	}
	return (0);
}

int	is_shift_direction_key(char *buffer)
{
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 49 && \
	buffer[3] == 59 && buffer[4] == 50 && (buffer[5] > 64 && buffer[5] < 69))
		return (1);
	return (0);
}

int	is_shift_up(char buffer5)
{
	if (buffer5 == 65)
		return (1);
	return (0);
}

int	is_shift_down(char buffer5)
{
	if (buffer5 == 66)
		return (1);
	return (0);
}

int	is_shift_right(char buffer5)
{
	if (buffer5 == 67)
		return (1);
	return (0);
}

int	is_shift_left(char buffer5)
{
	if (buffer5 == 68)
		return (1);
	return (0);
}

int	is_option_c(char *buffer)
{
	if (buffer[0] == -61 && buffer[1] == -89 && buffer[2] == 0)
		return (1);
	return (0);
}

int	is_option_v(char *buffer)
{
	if (buffer[0] == -30 && buffer[1] == -120 && buffer[2] == -102 && \
			buffer[3] == 0)
		return (1);
	return (0);
}

int	is_option_right(char *buffer)
{
	if (buffer[0] == 27 && buffer[1] == 27 && buffer[2] == 91 && \
			buffer[3] == 67)
		return (1);
	return (0);
}

int	is_option_left(char *buffer)
{
	if (buffer[0] == 27 && buffer[1] == 27 && buffer[2] == 91 && \
			buffer[3] == 68)
		return (1);
	return (0);
}

int	is_option_key(char *buffer)
{
	if (is_option_left(buffer) || is_option_right(buffer) || \
			is_option_v(buffer) || is_option_c(buffer))
		return (1);
	return (0);
}

int	is_eot(char *buffer)
{
	if (buffer[0] == 4 && buffer[1] == 0)
		return (1);
	return (0);
}
