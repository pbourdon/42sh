/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 08:56:01 by hlouar            #+#    #+#             */
/*   Updated: 2016/05/23 09:03:27 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*getpwd(void)
{
	char	*tmp;
	char	*dst;

	tmp = ft_memalloc(1024);
	if (getcwd(tmp, 1024) != NULL)
	{
		dst = ft_strdup(tmp);
		free(tmp);
		return (dst);
	}
	return (NULL);
}

char	*changepwd3(t_data *data, char *str, char *str2)
{
	if (data->oldpwd)
		data->voldpwd = ft_strdup(data->oldpwd);
	else
		data->voldpwd = ft_strdup(str2);
	if (data->oldpwd)
		str = ft_strjoin("OLDPWD=", data->oldpwd);
	else
		str = ft_strjoin("OLDPWD=", str2);
	return (str);
}

char	**changepwd2(t_data *data, char **tab, char *str)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	while (data->env[i])
	{
		if (rognagestring(data->env[i], "PWD=") == 1)
		{
			tab[o] = ft_strjoin("PWD=", str);
			o++;
			i++;
		}
		else if (rognagestring(data->env[i], "OLDPWD=") == 1)
		{
			tab[o] = changepwd3(data, tab[o], str);
			o++;
			i++;
		}
		tab[o] = ft_strdup(data->env[i]);
		o++;
		i++;
	}
	tab[o] = NULL;
	return (tab);
}

void	changepwdenv(t_data *data)
{
	int		i;
	char	**tab;
	int		o;
	char	*str;

	str = getpwd();
	o = 0;
	tab = (char **)malloc(sizeof(char *) * (ft_strlentab(data->env) + 1));
	i = 0;
	tab = changepwd2(data, tab, str);
	if (data->turn == 1)
		freetab(data->env);
	data->env = newtab(tab);
	freetab(tab);
	free(str);
}

void	gethome(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strstr(data->env[i], "HOME=") != NULL)
		{
			data->home = ft_strsub(data->env[i], 5, ft_strlen(data->env[i]));
			return ;
		}
		i++;
	}
	data->home = NULL;
}
