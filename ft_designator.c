/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_designator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourdon <pbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 19:14:12 by pbourdon          #+#    #+#             */
/*   Updated: 2016/10/15 19:01:02 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char			*ft_replace_designator(char *command, int index)
{
	if (command[index] <= '9' && command[index] >= '0')
		return (ft_replace_designator_norm(ft_atoi(command + index), command));
	else if (command[index] == '-' && (command[index + 1] >= '0' && command[index + 1] <= '9'))
		return (ft_replace_designator_rev(ft_atoi(command + index), command));
	else if (command[index] == '!')
		return (ft_replace_designator_rev(-1, command));
	else if (command[index] == '?')
		return (ft_replace_designator5(command + 1 + index, command));
	else if (command[index] == '#')
		return (ft_replace_designator6(command));
	else
		return (ft_replace_designator4(command + index, command));
	return (command);
}

char			*ft_check_designator(char *command, int *fake)
{
	int			index;
	char		*replace;
	char		*final;
	int			index2;
	int			index3;
	int			display;

	display = 0;
	index3 = 0;
	index = 0;
	index2 = 0;
	final = malloc(sizeof(char) * 4096);
	ft_bzero(final, 4096);
	while (command[index] != '\0')
	{
		if (command[index] == '!')
		{
			display = 1;
			if ((replace = ft_replace_designator(command, index + 1)) == NULL)
			{
				*fake = 1;
				return (command);
			}
			while (replace[index3] != '\0')
			{
				final[index2] = replace[index3];
				index2++;
				index3++;
			}
			index3 = 0;
			while (command[index] != ' ' && command[index] != '\t' && command[index] != '\0')
				index++;
		}
		else
		{
			final[index2] = command[index];
			index2++;
			index++;
		}
	}
	if (display == 1)
		ft_putendl(final);
	return (final);
}
