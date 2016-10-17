/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_designator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourdon <pbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 11:57:16 by pbourdon          #+#    #+#             */
/*   Updated: 2016/10/17 12:10:40 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char		*ft_error_event_char(char *command, int display)
{
	if (display != 0)
	{
		ft_putstr_fd("sh : ", 2);
		ft_putstr_fd(command, 2);
		ft_putendl_fd(": event not found", 2);
	}
	return (NULL);
}

char		*ft_error_event_char2(char *command, int display, char *str)
{
	if (display != 0)
	{
		ft_putstr_fd("sh : ", 2);
		ft_putstr_fd(command, 2);
		ft_putendl_fd(": event not found", 2);
	}
	ft_strdel(&str);
	return (NULL);
}

char		*ft_strdup_special(char *source, char *dest)
{
	int		index;

	index = 0;
	dest = malloc(sizeof(char) * ft_strlen(source));
	while (source[index] != '\0' && source[index] != '\t' && source[index] !=
			' ')
	{
		dest[index] = source[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}
