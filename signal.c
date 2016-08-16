/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 10:16:05 by pguzman           #+#    #+#             */
/*   Updated: 2016/08/04 10:22:40 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h" 

void	sig_handler(int a)
{
	struct winsize	w;

	a = 0;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	shell.shell_win_size = w.ws_col;
	update_cursor();
}
