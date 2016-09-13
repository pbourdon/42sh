/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 15:02:07 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/13 17:14:09 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		print_cursor_fd_2()
{
	ft_putstr_fd("Cursor : \n position_line : ", 2);
	ft_putnbr_fd(g_cursor.position_line, 2);
	ft_putstr_fd("\n position_x_rel : ", 2);
	ft_putnbr_fd(g_cursor.position_x_rel, 2);
	ft_putstr_fd("\n position_y_rel : ", 2);
	ft_putnbr_fd(g_cursor.position_y_rel, 2);
	//  ft_putstr_fd("\n position_y_abs : ", 2);
	//  ft_putnbr_fd(g_cursor.position_y_abs, 2);
	ft_putstr_fd("\n",2);
}

void		print_shell_fd_2()
{
	t_history *h;

	h = g_shell.history;
	ft_putstr_fd("Shell : \n shell_line : ", 2);
	ft_putstr_fd(g_shell.shell_line, 2);
	ft_putstr_fd("\n length_line : ", 2);
	ft_putnbr_fd(g_shell.length_line, 2);
	ft_putstr_fd("\n shell_win_size :", 2);
	ft_putnbr_fd(g_shell.shell_win_size, 2);
	ft_putstr_fd("\n shell_line_original :", 2);
	ft_putstr_fd(g_shell.shell_line_original, 2);
	ft_putstr_fd("\n history_index :", 2);
	ft_putnbr_fd(g_shell.history_index, 2);
	ft_putstr_fd("\n backslash_index :", 2);
	ft_putnbr_fd(g_shell.backslash_index, 2);
	ft_putstr_fd("\n shell_backslash_level :", 2);
	ft_putnbr_fd(g_shell.shell_backslash_level, 2);
	ft_putstr_fd("\n selected_start :", 2);
	ft_putnbr_fd(g_shell.selected_start, 2);
	ft_putstr_fd("\n selected_end :", 2);
	ft_putnbr_fd(g_shell.selected_end, 2);
	ft_putstr_fd("\n selected_copy :", 2);
	ft_putstr_fd(g_shell.selected_copy, 2);
	ft_putstr_fd("\n last_backslash :", 2);
	ft_putnbr_fd(g_shell.last_backslash, 2);
	ft_putstr_fd("\n", 2);

	// ft_putstr_fd("\n shell_history_0 :\n", 2);
	// while(h)
	// {
	// if (h->str != NULL)
	// {
	//   ft_putstr_fd(h->str, 2);
	//   ft_putstr_fd("\n", 2);
	// }
	// h = h->next;
	// }
}

void		sig_handler3(int sign)
{
	sign = 1;
	g_shell.shell_fd_0 = dup(0);
	close(0);
}

void		sig_handler2(int sign)
{
	sign = 1;
	ft_putendl("");
}

void		shell_listening_char(void)
{
	struct winsize	w;
	char			*buffer;

	while (1)
	{
		signal(SIGINT, sig_handler3);
		signal(SIGQUIT, sig_handler3);
		signal(SIGTSTP, sig_handler3);
		buffer = ft_strnew(8);
		update_shell_line_original();
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		g_shell.shell_win_size = w.ws_col;
		prepare_to_listen(buffer);
		if (listen(buffer))
			break ;
		update_cursor();
		print_shell_fd_2();
		print_cursor_fd_2();
		ft_strdel(&buffer);
	}
	signal(SIGINT, sig_handler2);
	signal(SIGQUIT, sig_handler2);
	signal(SIGTSTP, sig_handler2);
	ft_strdel(&buffer);
}

void		prepare_to_listen(char buffer[9])
{
	int				ret;

	ft_bzero(buffer, 9);
	signal(SIGWINCH, sig_handler);
	ret = read(0, buffer, 8);
	if (g_shell.shell_fd_0)
	{
		dup2(g_shell.shell_fd_0, 0);
		if (ret == -1)
		{
			buffer[0] = 0;
			buffer[1] = 0;
		}
		g_shell.shell_fd_0 = 0;
	}
	if (ret > -1)
		buffer[ret] = '\0';
}

void		delete_selection_if_other_than_option(char *buffer)
{
	int				temp;

	if (!is_option_left(buffer) && !is_option_right(buffer))
	{
		if (g_shell.selected_end != -1 && g_shell.selected_start != -1)
		{
			g_shell.selected_end = -1;
			g_shell.selected_start = -1;
			temp = g_cursor.position_line;
			press_home_key();
			press_printable_char(" ");
			press_backspace_key();
			while (g_cursor.position_line < temp)
				press_right_key();
		}
	}
}
