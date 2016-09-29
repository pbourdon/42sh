/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 13:54:34 by cmichaud          #+#    #+#             */
/*   Updated: 2016/09/29 16:51:03 by pguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char		*get_key_value(char *key, char **env)
{
	int		i;
	char	*mpt;

	i = -1;
	while (env && env[++i])
	{
		mpt = ft_strchr(env[i], '=');
		*mpt = 0;
		if (!ft_strcmp(env[i], key))
		{
			*mpt = '=';
			mpt = ft_strdup(mpt + 1);
			free(key);
			return (mpt);
		}
		*mpt = '=';
	}
	free(key);
	return (NULL);
}

char		*replace_forr_home(char *src, char *pos, char *to_add, int cut)
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
	i += cut;
	while (src && src[i] && src[++i])
		dest[++j] = src[i];
	dest[++j] = 0;
	free(to_add);
	free(src);
	return (dest);
}

char		*lets_replace_var(char *str, int i, t_data *data)
{
	int			k;
	char		c;
	char		*key;
	char		*value;

	k = i;
	while (str[++k])
		if (str[k] == '\\' || str[k] == '\'' || str[k] == '"' || str[k] == ' ')
			break ;
	c = str[k];
	str[k] = 0;
	key = ft_strdup(str + i + 1);
	str[k] = c;
	if ((value = get_key_value(key, data->env)))
		return (replace_forr_home(str, str + i, value, k - i));
	k = i;
	while (str[++k])
		if (str[k] == '\\' || str[k] == '\'' || str[k] == '"' || str[k] == ' ')
			break ;
	i -= 1;
	while (str[k] && str[++k])
		str[++i] = str[k];
	while (i < k)
		str[++i] = 0;
	return (str);
}

char		*replace_str_with_var(char *str, int i, t_data *data)
{
	int k;
	int j;

	k = -1;
	j = -1;
	if (str[i + 1] == '\'' || str[i + 1] == '"')
	{
		while (str[++j])
		{
			if (j != i)
				str[++k] = str[j];
		}
		str[++k] = 0;
		return (str);
	}
	if (str[i + 1] == '\\')
		return (str);
	return (lets_replace_var(str, i, data));
}

char		*search_var(char *str, t_data *data, int inib, int quote)
{
	int		i;

	i = -1;
	while (str && str[++i])
	{
		if (quote != '\'' && !inib && str[i] == '$' &&\
			(str[i + 1] && str[i + 1] != ' '))
			str = replace_str_with_var(str, i, data);
		if (!(quote + inib) && str[i] == '\\')
			inib = 1;
		else
			inib = 0;
		quote = quote_norm(inib, quote, str[i]);
	}
	return (str);
}
