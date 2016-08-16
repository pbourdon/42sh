/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_words.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 16:03:23 by pguzman           #+#    #+#             */
/*   Updated: 2016/08/03 16:03:39 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		get_next_word_after(char *str, int c)
{
	while (str[c])
	{
		if (str[c] == ' ')
		{
			while (str[c + 1] == ' ')
				c++;
			return (c);
		}
		c++;
	}
	return (-1);
}

int		get_next_word_before(char *str, int c)
{
	while (str[c])
	{
		if (str[c] != ' ')
		{
			while (str[c - 1] != ' ')
			{
				c--;
			}
			return (c);
		}
		c--;
	}
	return (-1);
}
