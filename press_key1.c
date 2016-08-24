/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <pguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 16:13:17 by pguzman           #+#    #+#             */
/*   Updated: 2016/08/24 11:15:03 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	movements_delete(int a)
{
	int h[2];

	tputs(tgetstr("cd", NULL), 0, tputs_putchar);
	h[0] = ft_putstr_i(g_shell.shell_line, g_cursor.position_line);
	h[1] = h[0];
	while (h[0] - 1 > 0)
	{
		move_cursor_right(g_cursor, g_shell);
		h[0]--;
	}
	if ((g_cursor.position_x_rel == g_shell.shell_win_size - 1) && \
			g_cursor.position_line != g_shell.length_line)
	{
		ft_putstr(" ");
		tputs(tgetstr("le", NULL), 0, tputs_putchar);
	}
	move_cursor_right(g_cursor, g_shell);
	while (h[1] - a > 0)
	{
		go_left(g_cursor, g_shell);
		move_cursor_left(g_cursor, g_shell);
		h[1]--;
	}
}

void	press_backspace_key(void)
{
	if (g_cursor.position_line > 0 && g_shell.backslash_index != 0)
	{
		g_shell.shell_line = del_from_arr(g_shell.shell_line, g_cursor.position_line);
		g_shell.length_line--;
		press_left_key();
		movements_delete(0);
	}
}

void	press_delete_key(void)
{
	if (g_cursor.position_line >= 0 && g_cursor.position_line != g_shell.length_line)
	{
		g_shell.shell_line = del_from_arr(g_shell.shell_line, \
				g_cursor.position_line + 1);
		g_shell.length_line--;
		movements_delete(0);
	}
}

void	print_history(t_history *history)
{
	t_history *his;

	his = history;
	while (his)
	{
		 ft_putstr_fd(his->str, 2);
		 ft_putstr_fd("\n", 2);
		his = his->next;
	}
}

void	press_up_key(void)
{
	t_history *history;
	if (g_shell.history_index > 0)
	{
		history = g_shell.history;
		if (g_shell.backslash_index != -1)
		{
			g_shell.history_index--;
			if (g_shell.history_index > 0)
				replace_shell_backslash_line(get_history_i(g_shell.history_index \
							- 1));
			if (g_shell.history_index == 0)
				g_shell.history_index++;
		}
		else if (g_shell.history_index != 1)
		{
			g_shell.history_index--;
			replace_shell_line(get_history_i(g_shell.history_index - 1));
		}
	}
}

void	press_down_key(void)
{
	t_history *history;

	history = g_shell.history;
	if (g_shell.history_index < get_history_length(history))
	{
		if (g_shell.backslash_index != -1)
			replace_shell_backslash_line(get_history_i(g_shell.history_index));
		else
			replace_shell_line(get_history_i(g_shell.history_index));
		g_shell.history_index++;
	}
	else if (g_shell.history_index == get_history_length(history))
	{
		g_shell.history_index = get_history_length(history) + 1;
		if (g_shell.backslash_index == -1)
			replace_shell_line(g_shell.shell_line_original);
		else
			replace_shell_backslash_line(g_shell.shell_line_original);
	}
}

void	press_left_key(void)
{
	if (g_cursor.position_line > 0 && g_shell.backslash_index != 0)
	{
		go_left(g_cursor, g_shell);
		move_cursor_left(g_cursor, g_shell);
	}
	if (g_shell.backslash_index > 0)
		g_shell.backslash_index--;
}

void	press_right_key(void)
{
	if (g_cursor.position_line < g_shell.length_line)
	{
		if (g_shell.backslash_index != -1)
			g_shell.backslash_index++;
		go_right(g_cursor, g_shell);
		move_cursor_right(g_cursor, g_shell);
	}
}

void	press_home_key(void)
{
	int h;

	h = g_cursor.position_line;
	while (h > 0)
	{
		if (g_shell.backslash_index == 0)
			break ;
		go_left(g_cursor, g_shell);
		move_cursor_left(g_cursor, g_shell);
		if (g_shell.backslash_index > 0)
			g_shell.backslash_index--;
		h--;
	}
}

void	press_end_key(void)
{
	int h;

	h = g_cursor.position_line;
	while (h < g_shell.length_line)
	{
		if (g_shell.backslash_index != -1)
			g_shell.backslash_index++;
		go_right(g_cursor, g_shell);
		move_cursor_right(g_cursor, g_shell);
		h++;
	}
}

void	press_printable_char(char *buffer)
{
	if (buffer[0] != 0 && !is_enter_key(buffer))
	{
		g_shell.shell_line = add_to_array(g_shell.shell_line, buffer[0], \
				g_cursor.position_line, g_shell.length_line);
		g_shell.length_line++;
		movements_delete(1);
		if (g_shell.backslash_index >= 0)
			g_shell.backslash_index++;
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
	while (i < g_shell.length_line)
	{
		j = 0;
		if (!check_char(q, a, g_shell.shell_line[i]))
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
		g_shell.backslash_index = 0;
		g_shell.shell_backslash_level++;
		g_shell.last_backslash = g_shell.length_line;
		ft_putstr("\n? ");
		return (0);
	}
}

int		backslash_at_the_end(void)
{
	if (g_shell.shell_line[g_shell.length_line - 1] == '\\')
	{
		g_shell.backslash_index = 0;
		g_shell.shell_line[g_shell.length_line - 1] = ' ';
		g_shell.shell_backslash_level++;
		g_shell.last_backslash = g_shell.length_line;
		ft_putstr("\n? ");
		return (1);
	}
	return (0);
}

int		press_enter_key(void)
{
	press_end_key();
	if (backslash_at_the_end() || !parenthesis_closed())
		return (0);
	if (ft_strcmp(g_shell.shell_line, "") != 0 && g_shell.shell_heredoc == 0)
		add_to_history(g_shell.history, g_shell.shell_line);
	// ft_bzero(g_shell.shell_line, 1000);
	g_shell.backslash_index = -1;
	if (g_shell.shell_heredoc == 0)
		g_shell.history_index = get_history_length();
 	if (ft_strcmp("<<", g_shell.shell_line) == 0)
		g_shell.shell_heredoc = 1;
	ft_putstr("\n");
	return (1);
}

void	press_shift_direction_key(char *buffer)
{
	// ft_putnbr_fd(buffer[5], 2);
	if (is_shift_right(buffer[5]))
		press_shift_right(g_cursor, g_shell);
	else if (is_shift_left(buffer[5]))
		press_shift_left(g_cursor, g_shell);
	else if (is_shift_up(buffer[5]))
		press_shift_up();
	else if (is_shift_down(buffer[5]))
		press_shift_down();
}

void	press_shift_left(void)
{
	int index_nw;
	int index_c;

	index_c = g_cursor.position_line - 1;
	index_nw = get_next_word_before(g_shell.shell_line, index_c);
	if (index_nw < g_shell.last_backslash)
		index_nw = g_shell.last_backslash;
	while (index_c >= index_nw)
	{
		if (g_shell.backslash_index > 0)
			g_shell.backslash_index--;
		go_left(g_cursor, g_shell);
		move_cursor_left(g_cursor, g_shell);
		index_c--;
	}
}

void	press_shift_right(void)
{
	int index_nw;
	int index_c;

	index_c = g_cursor.position_line;
	index_nw = get_next_word_after(g_shell.shell_line, index_c);
	while (index_c <= index_nw)
	{
		if (g_shell.backslash_index != -1)
			g_shell.backslash_index++;
		go_right(g_cursor, g_shell);
		move_cursor_right(g_cursor, g_shell);
		index_c++;
	}
}

void	press_shift_up(void)
{
	int h;
	int k;

	k = g_shell.shell_win_size;
	h = g_cursor.position_line;
	while (h > 0 && k > 0)
	{
		if (g_shell.backslash_index == 0)
			break ;
		go_left(g_cursor, g_shell);
		move_cursor_left(g_cursor, g_shell);
		if (g_shell.backslash_index > 0)
			g_shell.backslash_index--;
		h--;
		k--;
	}
}

void	press_shift_down(void)
{
	int h;
	int k;

	k = g_shell.shell_win_size;
	h = g_cursor.position_line;
	while (h < g_shell.length_line && k > 0)
	{
		if (g_shell.backslash_index != -1)
			g_shell.backslash_index++;
		go_right(g_cursor, g_shell);
		move_cursor_right(g_cursor, g_shell);
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
	if (g_shell.selected_start != -1 && g_shell.selected_end != -1)
	{
		if (ft_strcmp(g_shell.selected_copy, "") != 0)
			ft_strdel(&g_shell.selected_copy);
		g_shell.selected_copy = extract_str(g_shell.shell_line, \
				g_shell.selected_start, g_shell.selected_end);
	}
}

void	press_option_v(void)
{
	char	*str;
	size_t	i;
	char	a[2];

	i = 0;
	str = g_shell.selected_copy;
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
	temp = g_cursor.position_line;
	if (g_cursor.position_line > 0)
	{
		if (g_shell.selected_end == g_shell.selected_start)
		{
			g_shell.selected_start = g_cursor.position_line;
			g_shell.selected_end = g_cursor.position_line;
			g_shell.selected_start--;
		}
		else if (g_shell.selected_end == g_cursor.position_line)
			g_shell.selected_end--;
		else if (g_shell.selected_start == g_cursor.position_line)
			g_shell.selected_start--;
	}
	press_left_key();
	press_printable_char(a);
	press_backspace_key();
	while (g_cursor.position_line < temp - 1)
		press_right_key();
}

void	press_option_right(void)
{
	int		temp;

	temp = g_cursor.position_line;
	if (g_cursor.position_line < g_shell.length_line)
	{
		if (g_shell.selected_end == g_shell.selected_start)
		{
			g_shell.selected_start = g_cursor.position_line;
			g_shell.selected_end = g_cursor.position_line + 1;
		}
		else if (g_shell.selected_end == g_cursor.position_line)
			g_shell.selected_end++;
		else if (g_shell.selected_start == g_cursor.position_line)
			g_shell.selected_start++;
	}
	press_left_key();
	press_printable_char(" ");
	press_backspace_key();
	while (g_cursor.position_line < temp + 1)
	{
		if (g_cursor.position_line == g_shell.length_line)
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
