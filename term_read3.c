/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_read3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/28 16:53:26 by bde-maze          #+#    #+#             */
/*   Updated: 2016/09/27 16:16:08 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int			since_last(int k)
{
	int i;
	int a;

	i = 0;
	a = k;
	while (g_shell.shell_line[a] != '\n')
	{
		if (a == 0)
			return (g_cursor.position_line - g_shell.last_backslash + 3);
		a--;
		i++;
	}
	if (i == 0)
	{
		a--;
		while (g_shell.shell_line[a] != '\n')
		{
			if (a == 0)
				return (g_cursor.position_line - g_shell.last_backslash + 3);
			a--;
			i++;
		}
		i++;
	}
	return (i);
}

int			ft_strchr_i(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != c)
	{
		i++;
	}
	return (i);
}

void		go_right(void)
{
	if (g_cursor.position_x_rel == g_shell.shell_win_size - 1 \
			|| g_shell.shell_line[g_cursor.position_line] == '\n')
	{
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, tputs_putchar);
		tputs(tgetstr("do", NULL), 0, tputs_putchar);
	}
	else
	{
		tputs(tgoto(tgetstr("nd", NULL), 0, 0), 0, tputs_putchar);
	}
}

int			get_n_line(void)
{
	if (g_shell.shell_win_size == 0)
		return (-1);
	if (g_shell.shell_backslash_level > 0)
		return ((g_shell.backslash_index + 3) / g_shell.shell_win_size);
	return ((g_cursor.position_line + 6) / g_shell.shell_win_size);
}

int			get_pos_l(void)
{
	if (g_shell.shell_win_size == 0)
		return (-1);
	if (g_shell.shell_backslash_level > 0)
		return ((g_shell.backslash_index + 2) % g_shell.shell_win_size);
	if ((g_cursor.position_line + 6) % g_shell.shell_win_size == 0)
		return (0);
	else
		return (((g_cursor.position_line + 6) % g_shell.shell_win_size));
}

int			get_pos_jump2(void)
{
	int a;
	int i;

	i = 0;
	a = 0;
	while (i < g_cursor.position_line)
	{
		if (g_shell.shell_line[i] == '\n')
			a++;
		i++;
	}
	return (a + ((g_cursor.position_line + 6) / g_shell.shell_win_size));
}

int			get_pos_back2(void)
{
	int a;
	int i;

	i = 0;
	a = 0;
	while (i < g_cursor.position_line)
	{
		if (g_shell.shell_line[i] == '\n')
			a++;
		i++;
	}
	return (a + ((g_cursor.position_line + 2) / g_shell.shell_win_size));
}

int			get_n_line2(void)
{
	if (g_shell.shell_win_size == 0)
		return (-1);
	if (g_shell.backslash_index == -1)
	{
		return (get_pos_jump2());
	}
	if (g_shell.shell_backslash_level > 0)
		return (get_pos_back2());
	return ((g_cursor.position_line + 6) / g_shell.shell_win_size);
}

int aux1()
{
	int i;
	int j;

	i = 0;
	j = g_cursor.position_line;
	while (g_shell.shell_line[j - 1] != '\n')
	{
		if (j == 1)
			break ;
		j--;
		i++;
	}
		return  i % g_shell.shell_win_size;
}
int aux2()
{
	int i;
	int j;

	i = 0;
	j = g_cursor.position_line;
	while (g_shell.shell_line[j - 1] != '\n')
	{
		if (j == 1)
			break ;
		j--;
		i++;
	}
		return  (i + 2) % g_shell.shell_win_size;
}

int			get_pos_jump(void)
{
	if (ft_strchr_i(g_shell.shell_line, '\n') >= g_cursor.position_line)
	{
		if ((g_cursor.position_line + 6) % g_shell.shell_win_size == 0)
			return (0);
		else
			return (((g_cursor.position_line + 6) % g_shell.shell_win_size));
	}
	else
	{
			return aux1();
	}
}

int			get_pos_back(void)
{
	ft_putstr_fd("HERE\n", 2);
	if (g_shell.backslash_index == -1)
	{
		if (ft_strchr_i(g_shell.shell_line, '\n') >= g_cursor.position_line)
		{
			if ((g_cursor.position_line + 2) % g_shell.shell_win_size == 0)
				return (0);
			else
				return (((g_cursor.position_line + 2 - g_shell.last_backslash) \
							% g_shell.shell_win_size));
		}
		else
			return ((since_last(g_cursor.position_line) - 1) \
					% g_shell.shell_win_size);
	}
	else
		return ((since_last(g_cursor.position_line) - 1) \
				% g_shell.shell_win_size);
}

int jump_after_last(int a)
{
	int i;

	i = a;
	while (i < g_shell.length_line)
	{
		if (g_shell.shell_line[i] == '\n')
		{
				return(1);
		}
		i++;
	}
	return (0);
}

int jump_after_last_and_here(int a)
{
	int i;

	i = g_shell.last_backslash;
	while (i != a)
	{
		if (g_shell.shell_line[i] == '\n')
		{
			return (1);
		}
		i++;
	}
	return (0);
}
int			get_pos_backv2(void)
{

		if (jump_after_last(g_shell.last_backslash))
		{
			if (!jump_after_last_and_here(g_cursor.position_line))
			{
				if ((g_cursor.position_line - g_shell.last_backslash + 2) % g_shell.shell_win_size == 0)
					return (0);
				else
					return (((g_cursor.position_line - g_shell.last_backslash + 2) % g_shell.shell_win_size));
			}
			else
			{
					return aux1();
			}
		}
		else
		{
			return ((2 + g_shell.backslash_index) % g_shell.shell_win_size);
		}


}

int			get_pos_l2(void)
{
	if (g_shell.shell_win_size == 0)
		return (-1);
	if (g_shell.backslash_index == -1)
		return (get_pos_jump());
	else if (g_shell.shell_backslash_level > 0)
		return (get_pos_backv2());
	if ((g_cursor.position_line + 6) % g_shell.shell_win_size == 0)
		return (0);
	else
		return (((g_cursor.position_line + 6) % g_shell.shell_win_size));
}

void		go_left_jump(void)
{
	if (g_shell.backslash_index != -1)
	{
		g_shell.backslash_index--;
		g_cursor.position_line--;
		tputs(tgoto(tgetstr("ch", NULL), 0, \
		get_pos_l2()), 1, tputs_putchar);
		g_shell.backslash_index++;
		g_cursor.position_line++;
	}
	else
	{
		g_cursor.position_line--;
		tputs(tgoto(tgetstr("ch", NULL), 0, \
		get_pos_l2()), 1, tputs_putchar);
		g_cursor.position_line++;
	}

}

void		go_left(void)
{
	if (g_cursor.position_x_rel == 0)
	{
		tputs(tgetstr("up", NULL), 0, tputs_putchar);
		if (ft_strchr(g_shell.shell_line, '\n'))
			go_left_jump();
		else if (g_shell.selected_end != -2)
		{
			tputs(tgoto(tgetstr("ch", NULL), 0, \
			g_shell.shell_win_size - 1), 1, tputs_putchar);
		}
	}
	else if (g_cursor.position_line != 0)
	{
		tputs(tgetstr("le", NULL), 0, tputs_putchar);
	}
}

void		update_cursor(void)
{
	if (ft_strchr(g_shell.shell_line, '\n'))
	{
		g_cursor.position_x_rel = get_pos_l2();
		g_cursor.position_y_rel = get_n_line2();
	}
	else
	{
		g_cursor.position_x_rel = get_pos_l();
		g_cursor.position_y_rel = get_n_line();
	}
}
