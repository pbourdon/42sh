/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 16:13:17 by pguzman           #+#    #+#             */
/*   Updated: 2016/08/04 10:14:29 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	movements_delete(int a)
{
	int h[2];

	tputs(tgetstr("cd", NULL), 0, tputs_putchar);
	h[0] = ft_putstr_i(shell.shell_line, cursor.position_line);
	h[1] = h[0];
	while (h[0] - 1 > 0)
	{
		move_cursor_right(cursor, shell);
		h[0]--;
	}
	if ((cursor.position_x_rel == shell.shell_win_size - 1) && \
			cursor.position_line != shell.length_line)
	{
		ft_putstr(" ");
		tputs(tgetstr("le", NULL), 0, tputs_putchar);
	}
	move_cursor_right(cursor, shell);
	while (h[1] - a > 0)
	{
		go_left(cursor, shell);
		move_cursor_left(cursor, shell);
		h[1]--;
	}
}

void	press_backspace_key(void)
{
	if (cursor.position_line > 0 && shell.backslash_index != 0)
	{
		shell.shell_line = del_from_arr(shell.shell_line, cursor.position_line);
		shell.length_line--;
		press_left_key();
		movements_delete(0);
	}
}

void	press_delete_key(void)
{
	if (cursor.position_line >= 0 && cursor.position_line != shell.length_line)
	{
		shell.shell_line = del_from_arr(shell.shell_line, \
				cursor.position_line + 1);
		shell.length_line--;
		movements_delete(0);
	}
}

void	print_history(t_history *history)
{
	t_history *his;

	his = history;
	while (his)
	{
		// ft_putstr_fd(his->str, 2);
		// ft_putstr_fd("\n", 2);
		his = his->next;
	}
}

void	press_up_key(void)
{
	t_history *history;

	if (shell.history_index > 0)
	{
		history = shell.history;
		if (shell.backslash_index != -1)
		{
			shell.history_index--;
			if (shell.history_index > 0)
				replace_shell_backslash_line(get_history_i(shell.history_index \
							- 1));
			if (shell.history_index == 0)
				shell.history_index++;
		}
		else if (shell.history_index != 1)
		{
			shell.history_index--;
			// ft_putnbr_fd(shell.history_index, 2);
			// ft_putstr_fd("\n\n", 2);
			print_history(history);
			replace_shell_line(get_history_i(shell.history_index - 1));
		}
	}
}

void	press_down_key(void)
{
	t_history *history;

	history = shell.history;
	if (shell.history_index < get_history_length(history))
	{
		if (shell.backslash_index != -1)
			replace_shell_backslash_line(get_history_i(shell.history_index));
		else
			replace_shell_line(get_history_i(shell.history_index));
		shell.history_index++;
	}
	else if (shell.history_index == get_history_length(history))
	{
		shell.history_index = get_history_length(history) + 1;
		if (shell.backslash_index == -1)
			replace_shell_line(shell.shell_line_original);
		else
			replace_shell_backslash_line(shell.shell_line_original);
	}
}

void	press_left_key(void)
{
	if (cursor.position_line > 0 && shell.backslash_index != 0)
	{
		go_left(cursor, shell);
		move_cursor_left(cursor, shell);
	}
	if (shell.backslash_index > 0)
		shell.backslash_index--;
}

void	press_right_key(void)
{
	if (cursor.position_line < shell.length_line)
	{
		if (shell.backslash_index != -1)
			shell.backslash_index++;
		go_right(cursor, shell);
		move_cursor_right(cursor, shell);
	}
}

void	press_home_key(void)
{
	int h;

	h = cursor.position_line;
	while (h > 0)
	{
		if (shell.backslash_index == 0)
			break ;
		go_left(cursor, shell);
		move_cursor_left(cursor, shell);
		if (shell.backslash_index > 0)
			shell.backslash_index--;
		h--;
	}
}

void	press_end_key(void)
{
	int h;

	h = cursor.position_line;
	while (h < shell.length_line)
	{
		if (shell.backslash_index != -1)
			shell.backslash_index++;
		go_right(cursor, shell);
		move_cursor_right(cursor, shell);
		h++;
	}
}

void	press_printable_char(char *buffer)
{
	if (buffer[0] != 0 && !is_enter_key(buffer))
	{
		shell.shell_line = add_to_array(shell.shell_line, buffer[0], \
				cursor.position_line, shell.length_line);
		shell.length_line++;
		movements_delete(1);
		if (shell.backslash_index >= 0)
			shell.backslash_index++;
	}
}

int		ft_strchr_i(char *s, char c)
{
	int				i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int		check_char(int *q, int a[], char ch)
{
	char	*str;
	int		y;

	str = "a({[]})`\"'";
	y = ft_strchr_i(str, ch);
	if (y)
	{
		if (y == 1)
			(a[0])++;
		else if (y == 2)
			(a[1])++;
		else if (y == 3)
			(a[2])++;
		else if (y == 4)
			(a[2])--;
		else if (y == 5)
			(a[1])--;
		else if (y == 6)
			(a[0])--;
		else if (y > 6 && y < 10)
			(*q)++;
		return (a[0] < 0 || a[1] < 0 || a[2] < 0) ? 0 : 1;
	}
	return (1);
}

int		check_par_and_quotes(int *q, int a[])
{
	int i;
	int j;

	i = 0;
	while (i < shell.length_line)
	{
		j = 0;
		if (!check_char(q, a, shell.shell_line[i]))
		{
			// ft_putstr_fd("END\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int		parenthesis_closed(void)
{
	int quotes_paired;
	int	par_paired[3];

	quotes_paired = 0;
	par_paired[0] = 0;
	par_paired[1] = 0;
	par_paired[2] = 0;
	if (!check_par_and_quotes(&quotes_paired, par_paired))
	{
		ft_putstr("\nSyntax error");
		return (2);
	}
	// ft_putnbr_fd(par_paired[0], 2);
	// ft_putnbr_fd(par_paired[1], 2);
	// ft_putnbr_fd(par_paired[2], 2);
	if ((quotes_paired % 2 == 0) && par_paired[0] == 0 && par_paired[1] == 0 \
			&& par_paired[2] == 0)
		return (1);
	else
	{
		shell.backslash_index = 0;
		shell.shell_backslash_level++;
		shell.last_backslash = shell.length_line;
		ft_putstr("\n? ");
		return (0);
	}
}

int		backslash_at_the_end(void)
{
	if (shell.shell_line[shell.length_line - 1] == '\\')
	{
		shell.backslash_index = 0;
		shell.shell_line[shell.length_line - 1] = ' ';
		shell.shell_backslash_level++;
		shell.last_backslash = shell.length_line;
		ft_putstr("\n? ");
		return (1);
	}
	return (0);
}

int		press_enter_key(void)
{
	press_end_key();
	// ft_putstr_fd("\nparenthesis_closed: ", 2);
	// ft_putstr_fd("\n", 2);
	if (backslash_at_the_end() || !parenthesis_closed())
		return (0);
	if (ft_strcmp(shell.shell_line, "exit") == 0)
		exit(0);
	if (ft_strcmp(shell.shell_line, "") != 0)
		add_to_history();
	// ft_bzero(shell.shell_line, 1000);
	shell.backslash_index = -1;
	shell.history_index = get_history_length();
	ft_putstr("\n");
	return (1);
}

void	press_shift_direction_key(char *buffer)
{
	// ft_putnbr_fd(buffer[5], 2);
	if (is_shift_right(buffer[5]))
		press_shift_right(cursor, shell);
	else if (is_shift_left(buffer[5]))
		press_shift_left(cursor, shell);
	else if (is_shift_up(buffer[5]))
		press_shift_up();
	else if (is_shift_down(buffer[5]))
		press_shift_down();
}

void	press_shift_left(void)
{
	int index_nw;
	int index_c;

	index_c = cursor.position_line - 1;
	index_nw = get_next_word_before(shell.shell_line, index_c);
	if (index_nw < shell.last_backslash)
		index_nw = shell.last_backslash;
	while (index_c >= index_nw)
	{
		if (shell.backslash_index > 0)
			shell.backslash_index--;
		go_left(cursor, shell);
		move_cursor_left(cursor, shell);
		index_c--;
	}
}

void	press_shift_right(void)
{
	int index_nw;
	int index_c;

	index_c = cursor.position_line;
	index_nw = get_next_word_after(shell.shell_line, index_c);
	while (index_c <= index_nw)
	{
		shell.backslash_index++;
		go_right(cursor, shell);
		move_cursor_right(cursor, shell);
		index_c++;
	}
}

void	press_shift_up(void)
{
	int h;
	int k;

	k = shell.shell_win_size;
	h = cursor.position_line;
	while (h > 0 && k > 0)
	{
		if (shell.backslash_index == 0)
			break ;
		go_left(cursor, shell);
		move_cursor_left(cursor, shell);
		if (shell.backslash_index > 0)
			shell.backslash_index--;
		h--;
		k--;
	}
}

void	press_shift_down(void)
{
	int h;
	int k;

	k = shell.shell_win_size;
	h = cursor.position_line;
	while (h < shell.length_line && k > 0)
	{
		if (shell.backslash_index != -1)
			shell.backslash_index++;
		go_right(cursor, shell);
		move_cursor_right(cursor, shell);
		h++;
		k--;
	}
}

char	*extract_str(char *str, int a, int b)
{
	char	*res;
	int		i;
	int		temp;

	i = 0;
	temp = b - a + 1;
	res = (char *)malloc(sizeof(*res) * (b - a + 2));
	res[b - a + 1] = '\0';
	while (i < (temp))
	{
		res[i] = str[a];
		a++;
		i++;
	}
	return (res);
}

void	press_option_c(void)
{
	if (shell.selected_start != -1 && shell.selected_end != -1)
	{
		if (ft_strcmp(shell.selected_copy, "") != 0)
			ft_strdel(&shell.selected_copy);
		shell.selected_copy = extract_str(shell.shell_line, \
				shell.selected_start, shell.selected_end);
	}
}

void	press_option_v(void)
{
	char	*str;
	size_t	i;
	char	a[2];

	i = 0;
	str = shell.selected_copy;
	a[1] = '\0';
	while (i < ft_strlen(str))
	{
		a[0] = str[i];
		press_printable_char(a);
		i++;
	}
}

void	go_inverse(void)
{
	char	a[2];

	a[0] = ' ';
	a[1] = '\n';
	tputs(tgetstr("mr", NULL), 0, tputs_putchar);
	press_home_key();
	press_printable_char(a);
	press_backspace_key();
}

void	press_option_left(void)
{
	char	a[2];
	int		temp;

	a[0] = ' ';
	a[1] = '\n';
	temp = cursor.position_line;
	if (cursor.position_line > 0)
	{
		if (shell.selected_end == shell.selected_start)
		{
			shell.selected_start = cursor.position_line;
			shell.selected_end = cursor.position_line;
			shell.selected_start--;
		}
		else if (shell.selected_end == cursor.position_line)
			shell.selected_end--;
		else if (shell.selected_start == cursor.position_line)
			shell.selected_start--;
	}
	press_left_key();
	press_printable_char(a);
	press_backspace_key();
	while (cursor.position_line < temp - 1)
		press_right_key();
}

void	press_option_right(void)
{
	int		temp;

	temp = cursor.position_line;
	if (cursor.position_line < shell.length_line)
	{
		if (shell.selected_end == shell.selected_start)
		{
			shell.selected_start = cursor.position_line;
			shell.selected_end = cursor.position_line + 1;
		}
		else if (shell.selected_end == cursor.position_line)
			shell.selected_end++;
		else if (shell.selected_start == cursor.position_line)
			shell.selected_start++;
	}
	press_left_key();
	press_printable_char(" ");
	press_backspace_key();
	while (cursor.position_line < temp + 1)
	{
		if (cursor.position_line == shell.length_line)
			break ;
		press_right_key();
	}
}

void	press_direction_key(char *buffer)
{
	if (is_up_key(buffer))
		press_up_key();
	else if (is_down_key(buffer))
		press_down_key();
	else if (is_left_key(buffer))
		press_left_key();
	else if (is_right_key(buffer))
		press_right_key();
}

void	press_option_key(char *buffer)
{
	if (is_option_c(buffer))
		press_option_c();
	else if (is_option_v(buffer))
		press_option_v();
	else if (is_option_right(buffer))
		press_option_right();
	else if (is_option_left(buffer))
		press_option_left();
}
