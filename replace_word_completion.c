/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_word_completion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 10:36:16 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/21 10:36:36 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		replace_word(char *new, int b_word)
{
	char	*buff;
	int		i;

	i = -1;
	buff = ft_strnew(8);
	while (++i < 8)
		buff[i] = 0;
	while (g_cursor.position_line != b_word + 1 && g_cursor.position_line)
		press_backspace_key();
	if (b_word == 0)
		press_backspace_key();
	i = -1;
	while (new[++i])
	{
		if (new[i] == ' ')
		{
			buff[0] = '\\';
			press_printable_char(buff);
		}
		buff[0] = new[i];
		press_printable_char(buff);
	}
	free(buff);
}

void		replace_cmd_cur_word(char *new, char *cmd, int b_word)
{
	if (!new || !new[0])
		return ;
	set_cur_end_word(cmd, b_word);
	replace_word(new, b_word);
}
