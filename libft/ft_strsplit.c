/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:56:01 by bde-maze          #+#    #+#             */
/*   Updated: 2016/01/12 13:56:04 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		height(char const *s, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int		lenght(const char *s, int i, int len, char c)
{
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static char		*prt(char const *s, char c, int i, char *str)
{
	int j;

	j = 0;
	while (s[i] != c && s[i] != '\0')
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char			**ft_strsplit(char const *s, char c)
{
	char			**tab;
	unsigned int	i;
	int				x;
	int				y;

	i = 0;
	x = 0;
	if (!s)
		return (NULL);
	tab = (char **)ft_memalloc(sizeof(char *) * (height(s, c) + 1));
	while (s[i] != '\0' && i < ft_strlen(s))
	{
		y = 0;
		if (s[i] != c)
		{
			y = lenght(s, i, y, c);
			tab[x] = (char *)ft_memalloc(sizeof(char) * (y + 1));
			tab[x] = prt(s, c, i, tab[x]);
			i = i + y - 1;
			x++;
		}
		i++;
	}
	tab[x] = NULL;
	return (tab);
}
