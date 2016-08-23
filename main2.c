/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 18:50:23 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/23 18:45:18 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// char			**make_the_split(char **tab, int y, int len, int i)
// {
	// char		**tab2;
	// int			j;
// 
	// j = 0;
	// tab2 = ft_memalloc(sizeof(char *) * ft_strlentab(tab));
	// while (j < i)
	// {
		// tab2 = ft_strdup(tab[j]);
		// j++;
	// }
	// 
	// return (tab2);
// }
// 
// char			**create_string_inib(char **tab, char inib, int i, int y)
// {
	// int			len;
	// 
	// len = 0;
	// y = ft_strlentab(tab);
	// while (y > i)
	// {
		// len = ft_strlen(tab[y]);
		// while (len > 0)
		// {
			// if (tab[y][len] == inib)
				// return (make_the_split(tab, y, len, i))
			// len--;
		// }
		// y--;
	// }
	// return (tab);
// }
// 
// char			which_inib(char *str)
// {
	// int			i;
// 
	// i = 0;
	// while (i <= ft_strlen(str))
	// {
		// if (str[i] == "\"" || str[i] == "'" || str[i] == "\\")
			// return (str[i]);
		// i++;
	// }
	// return (c);
// }
// 
// char			**check_inib(char **tab)
// {
	// int			i;
// 
	// i = 0;
	// while (tab[i])
	// {
		// if (ft_strchr(tab[i], "\"") != NULL || ft_strchr(tab[i], "'") != NULL || ft_strchr(tab[i], "\\") != NULL)
		// {
			// tab = create_string_inib(tab, which_inib(tab[i]), i, 0);
			// break ;
		// }
		// i++;
	// }
	// return (tab);
// }
// 

void			parsecommand(t_data *data, t_liste *liste)
{
	if (data->line[0] == '\0')
	{
		data->dspam = 1;
		return ;
	}
	data->args = ft_strsplit(data->line, ' ');
	// data->args = check_inib(data->args);
	if (ft_strcmp(data->line, "exit") == 0)
	{
		ft_putstr("trololo");
		get_tabhash(NULL, 1);
		free_list(liste);
		exit(0);
	}
	else if (ifitsredi(data) != 0)
	{
		mainredi(data);
		free(data->liste);
		freetab(data->oldtbe);
		return ;
	}
	else if (ft_strcmp(data->args[0], "env") == 0)
		callallenv(data);
	else if (ft_strcmp(data->args[0], "setenv") == 0)
		callsetenv(data);
	else if (ft_strcmp(data->args[0], "unsetenv") == 0)
		callunsetenv(data);
	else if (ft_strcmp(data->args[0], "cd") == 0)
		cdcall(data);
	else
		forkall(data);
}

int				switch_case(t_tk *ptr, int nb_redir, int nb_redir2)
{
	if (ptr->tk == 3 && ft_strncmp(ptr->arg, "|", 1) != 0 && ptr->next == NULL)
	{
		ft_putendl("Missing name for redirect.");
		return (-1);
	}
	else if (nb_redir > 1 || nb_redir2 < -1)
	{
		ft_putendl("Ambigous output redirect.");
		return (-1);
	}
	else if (ptr->tk == 3 && ft_strncmp(ptr->arg, "|", 1) == 0
	&& ptr->next == NULL)
	{
		ft_putendl("Invalid null command.");
		return (-1);
	}
	return (0);
}

void			go_free(char *cwd, char *hostname, char *curtime)
{
	free(cwd);
	free(hostname);
	free(curtime);
}
