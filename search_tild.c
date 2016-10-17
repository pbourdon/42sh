/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_tild.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 12:09:18 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/17 17:13:11 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char		*is_home(char **env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env && env[++i])
	{
		tmp = ft_strchr(env[i], '=');
		*tmp = 0;
		if (!ft_strcmp(env[i], "HOME"))
		{
			*tmp = '=';
			tmp = ft_strdup(tmp + 1);
			return (tmp);
		}
		*tmp = '=';
	}
	return (NULL);
}

char		*replace_for_home(char *src, char *pos, char *to_add)
{
	char	*dest;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	k = -1;
	dest = (char *)malloc(sizeof(char) * ft_strlen(src) + ft_strlen(to_add));
	while (src[++i] && src + i != pos)
		dest[++j] = src[i];
	while (to_add[++k])
		dest[++j] = to_add[k];
	while (src && src[++i])
		dest[++j] = src[i];
	dest[++j] = 0;
	free(to_add);
	free(src);
	return (dest);
}

char		*search_tild(char *str, t_data *data, int inib, int quote)
{
	int		i;
	char	*tmp;

	i = -1;
	str = ft_strdup(str);
	while (str && str[++i])
	{
		if (!quote && !inib && str[i] == '~' &&\
			(!str[i + 1] || str[i + 1] == ' ' || str[i + 1] == '/'))
		{
			if ((tmp = is_home(data->env)))
				str = replace_for_home(str, str + i, tmp);
		}
		if (!(quote + inib) && str[i] == '\\')
			inib = 1;
		else
			inib = 0;
		quote = quote_norm(inib, quote, str[i]);
	}
	return (str);
}
