/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   agreg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2016/08/20 17:28:19 by cmichaud          #+#    #+#             */
/*   Updated: 2016/08/20 17:28:20 by cmichaud         ###   ########.fr       */
||||||| merged common ancestors
/*   Created: 2016/08/15 13:49:02 by hlouar            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2016/08/18 17:57:46 by hlouar           ###   ########.fr       */
||||||| merged common ancestors
/*   Updated: 2016/08/15 13:49:05 by hlouar           ###   ########.fr       */
=======
/*   Updated: 2016/08/19 13:19:44 by cmichaud         ###   ########.fr       */
>>>>>>> res
=======
/*   Created: 2016/08/20 18:21:18 by hlouar            #+#    #+#             */
/*   Updated: 2016/08/20 18:21:20 by hlouar           ###   ########.fr       */
>>>>>>> 2f435cffb7ffd831a2fd9120e05eacb2978e1e65
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		isanum(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (-1);
	}
	return (1);
}

int		secondpart(char *str)
{
	int		i;
	int		o;
	char	*dst;

	i = 0;
	o = 0;
	dst = malloc(sizeof(char) * (ft_strlen(str) - (i + 1)));
	i = countstr(str, i);
	if (i == -2)
		return (-2);
	i = i + 1;
	while (str[i])
	{
		dst[o] = str[i];
		o++;
		i++;
	}
	dst[o] = '\0';
	if (isanum(dst) == 1 || dst[o - 1] == '-')
	{
		free(dst);
		return (1);
	} // leaks
	return (-1);
}

int		checkagred(char *str)
{
	int		i;
	int		o;
	char	*dst;

	o = 0;
	i = 0;
	while (str[i] != '>')
	{
		if (str[i] == '\0')
			return (-2);
		i++;
	}
	dst = malloc(sizeof(char) * (o + 1));
	while (o < i)
	{
		dst[o] = str[o];
		o++;
	}
	dst[o] = '\0';
	if (isanum(dst) == 1 && (secondpart(str) == 1))
	{
		free(dst);
		return (1);
	} // leaks
	return (-1);
}

char	*decoupe1(char *str)
{
	int		i;
	char	*dst;

	i = 0;
	while (str[i] != '>' && str[i])
		i++;
	dst = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '>' && str[i])
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*decoupe2(char *str)
{
	int		i;
	char	*dst;
	int		o;

	o = 0;
	i = 0;
	while (str[i] != '&' && str[i])
		i++;
	dst = malloc(sizeof(char) * (ft_strlen(str) - (i + 1)));
	i++;
	while (str[i])
	{
		dst[o] = str[i];
		i++;
		o++;
	}
	dst[o] = '\0';
	return (dst);
}
