/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_designator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourdon <pbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 19:14:12 by pbourdon          #+#    #+#             */
/*   Updated: 2016/10/22 09:50:56 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char			*ft_replace_designator(char *command, int index, int display,
				char *final)
{
	if (command[index] <= '9' && command[index] >= '0')
		return (ft_replace_designator_norm(ft_atoi(command + index), command,
display));
	else if (command[index] == '-' && (command[index + 1] >= '0' &&
command[index + 1] <= '9'))
		return (ft_replace_designator_rev(ft_atoi(command + index), command,
display));
	else if (command[index] == '!')
		return (ft_replace_designator_rev(-1, command, display));
	else if (command[index] == '?')
		return (ft_replace_designator5(command + 1 + index, command, display));
	else if (command[index] == '#')
		return (ft_replace_designator6(final));
	else
		return (ft_replace_designator4(command + index, command, display));
	return (command);
}

char			*ft_special(char *command, int index, int len, char *tmp)
{
	char		*final;

	while (command[index] != '\0')
	{
		if (command[index] == '!')
		{
			tmp = ft_replace_designator(command, index + 1, 0, NULL);
			len += ft_strlen(tmp);
			ft_strdel(&tmp);
		}
		index++;
	}
	index = 0;
	while (command[index] != '\0')
	{
		if (command[index] == '!' && command[index + 1] == '#')
			len += len;
		index++;
	}
	final = malloc(sizeof(char) * len);
	if (final != NULL)
		ft_bzero(final, len);
	return (final);
}

char			*ft_special_replace(char *command, int index, int *fake,
				char *final)
{
	char		*replace;

	if ((replace = ft_replace_designator(command, index + 1, 1, final)) == NULL)
	{
		*fake = 1;
		return (NULL);
	}
	return (replace);
}

char			*ft_replace_final(char *replace, char *final, int *index2)
{
	int			index3;

	index3 = 0;
	while (replace[index3] != '\0')
	{
		final[*index2] = replace[index3];
		*index2 = *index2 + 1;
		index3++;
	}
	ft_strdel(&replace);
	return (final);
}

char			*ft_check_designat(char *command, int *fake, int index,
	int index2)
{
	char		*replace;
	char		*final;
	int			display;

	display = 0;
	final = ft_special(command, 0, ft_strlen(command), NULL);
	while (command[index] != '\0')
	{
		if (command[index] == '!')
		{
			display = 1;
			if ((replace = ft_special_replace(command, index, fake, final))
				== NULL)
			{
				ft_strdel(&final);
				return (command);
			}
			final = ft_replace_final(replace, final, &index2);
			index = ft_adv_co(command, index);
		}
		else
			final[index2++] = command[index++];
	}
	final[index2] = '\0';
	return (ft_last_ope(final, display));
}
