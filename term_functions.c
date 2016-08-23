/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <pguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 10:23:04 by pguzman           #+#    #+#             */
/*   Updated: 2016/08/18 16:55:23 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int			term_init(t_term *term)
{
	if ((term->term_name = getenv("TERM")) == NULL)
		return (-1);
	tgetent(NULL, term->term_name);
	tcgetattr(0, &(term->term));
	tcgetattr(0, &term->term_copy);
	term->term.c_lflag &= ~(ICANON);
	term->term.c_lflag &= ~(ECHO);
	term->term.c_cc[VMIN] = 1;
	term->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &(term->term));
	return (1);
}

int			tputs_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int			ft_reset_term(struct termios term)
{
	if (tcsetattr(0, 0, &term) == -1)
		return (-1);
	tputs(tgetstr("ve", NULL), 1, tputs_putchar);
	return (0);
}
