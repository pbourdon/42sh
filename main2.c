/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 18:50:23 by bde-maze          #+#    #+#             */
/*   Updated: 2016/08/26 07:00:44 by cmichaud         ###   ########.fr       */
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

char			*cut(char *str, int pos, int inib)
{
	char		*tmp;
	int			len;

	tmp = str + pos - 1;
	len = ft_strlen(tmp);
	while (tmp[len] != inib)
		len--;
	tmp = ft_strncpy(tmp, tmp, len);
	return (tmp);
}

int				which_inib(char *str)
{
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(str);
	while (i <= len)
	{
		if (str[i] == '"' || str[i] == '\'' || str[i] == '\\')
			return (str[i]);
		i++;
	}
	return (i);
}

char			**sub_complete(char **tb, char **tb2, int i, int j)
{
	int			len;
	int			len2;
	char		**tab3;

	len = ft_strlentab(tb);
	len2 = ft_strlentab(tb2);
	ft_putendl("debug:split 1");
	tab3 = ft_memalloc(sizeof(char *) * (len + len2));
	ft_putendl("debug:split 2");
	while (tb[i])
	{
		tab3[i] = ft_strdup(tb[i]); 
		i++;
	}
	ft_putendl("debug:split 3");
	while (tb2[j])
	{
		tab3[i] = ft_strdup(tb2[j]);
		i++;
		j++;
	}
	ft_putendl("debug:split 4");
	return (tab3);
}

char			**complete_tab(char **tb, char *middle, char *str)
{
	int			i;
	int			j;
	char		**tb2;

	j = 0;
	i = ft_strlentab(tb);
	tb2 = ft_memalloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		tb2[j] = ft_strdup(tb[j]);
		j++;
	}
	tb2[j] = ft_strdup(middle);
	freetab(tb);
	str = str + (ft_strlen(middle) + 1);
	tb = ft_strsplit(str, ' ');
	return (sub_complete(tb2, tb, 0, 0));
}

char			**split(char *str, char *begin, char *middle)
{
	int			i;
	int			pos;
	char		inib;
	char		**tb;

	i = 0;
	pos = 0;
	if (ft_strstr(str, "\"") == NULL && ft_strstr(str, "'") == NULL && ft_strstr(str, "\\") == NULL)
		return (ft_strsplit(str, ' '));
	pos = which_inib(str);
	begin = ft_strnew(pos);
	inib = str[pos];
	begin = ft_strncpy(begin, str, pos - 1);
	middle = cut(str, pos, inib);
	tb = ft_strsplit(begin, ' ');
	free(begin);
	tb = complete_tab(tb, middle, str);
	return (tb);
}

int			is_a_word(int quote, int inib, char c)
{
	if ((quote + inib) && c != quote)
		return (1);
	else if (c != ' ' && c != '"' && c != '\'')
		return (1);
	return (0);
}

char		quote_norm(int inib, char quote, char c)
{
	if (quote && c == quote)
		quote = 0;
	else if (!inib && !quote && (c == '\'' || c == '"'))
		quote = c;
	return (quote);
}

int			ft_strlen_inib(char *str, int quote, int inib, int word)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (str && str[++i])
	{
		if (!(inib + quote) && word == 1 && str[i] == ' ' && (++len))
			while (!(word = 0) && str[i] && (str[i] == ' ' || str[i] == '\t'))
				if (!str[++i])
					break ; //return (len);
		if (!quote && !inib && str[i] == '\\')
			inib = 1;
		else
		{
			quote = quote_norm(inib, quote, str[i]);
			if (!word && is_a_word(quote, inib, str[i]))
				word = 1;
			inib = 0;
		}
	}
	word ? len += 1 : len;
	quote ? len = -1 : len;
	ft_putnbr(word);
	ft_putendl("<==word");
	ft_putnbr(len);
	ft_putendl("<==len");
	return (len);
}

int			ft_strlen_word_inib(char *str, int i, int inib, int quote)
{
	int		len;

	len = 0;
	while (str && str[++i])
	{
		if (!quote && !inib && str[i] == '\\')
			inib = 1;
		else
		{
			quote = quote_norm(inib, quote, str[i]);
			if (is_a_word(quote, inib, str[i]))
				len++;
			inib = 0;
		}
		if (!(inib + quote) && len && str[i] == ' ')
			return (len);
	}
	return (len);
}

char		*ft_strcpy_inib(char *dest, char *str, int i, int j)
{
	int inib;
	int quote;

	inib = 0;
	quote = 0;
	while (str && str[++i])
	{
		if (!quote && !inib && str[i] == '\\')
			inib = 1;
		else
		{
			quote = quote_norm(inib, quote, str[i]);
			if (is_a_word(quote, inib, str[i]))
				dest[++j] = str[i];
			inib = 0;
		}
		if (!(inib + quote) && j != -1 && str[i] == ' ')
			return (dest);
	}
	return (dest);
}

int			search_next_pos(char *str, int i, int inib, int quote)
{
	int		word;

	word = 0;
	while (str && str[++i])
	{
		if (!(inib + quote) && word == 1 && str[i] == ' ')
		{
			while (!(word = 0) && str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			return (i);
		}
		if (!quote && !inib && str[i] == '\\')
			inib = 1;
		else
		{
			quote = quote_norm(inib, quote, str[i]);
			if (!word && is_a_word(quote, inib, str[i]))
				word = 1;
			inib = 0;
		}
	}
	return (0);
}

char		**ft_split_inib(char **argv, char *str, int len, int i)
{
	int		cur_len;
	int		cur_pos;

	cur_pos = 0;
	while (++i < len)
	{
		ft_putnbr(cur_pos);
		ft_putstr("is it\n");
		cur_len = ft_strlen_word_inib(str, cur_pos - 1, 0, 0);
		argv[i] = (char *)malloc(sizeof(char) * (cur_len + 1));
		argv[i][cur_len] = 0;
		argv[i] = ft_strcpy_inib(argv[i], str, cur_pos - 1, -1);
		cur_pos = search_next_pos(str, cur_pos - 1, 0, 0);
	}
	return (argv);
}

char		**split_on_inib(char *str)
{
	int		len;
	char	**argv;

	len = ft_strlen_inib(str, 0, 0, 0);
	if (!len)
		ft_putendl(": Command not found.");
	if (len == -1)
		ft_putendl("Unmatched quote.");
	if (len <= 0)
		return (NULL);
	argv = (char **)malloc(sizeof(char *) * (len + 1));
	ft_putnbr(len);
	ft_putendl("len");
	argv = ft_split_inib(argv, str, len, -1);
	argv[len] = NULL;
	return (argv);
}

void			parsecommand(t_data *data, t_liste *liste)
{
	if (data->line[0] == '\0')
	{
		data->dspam = 1;
		return ;
	}
//	ft_putstr(data->line);
	if (!(data->args = split_on_inib(data->line)))
		return ;
	if (ft_strcmp(data->line, "exit") == 0)
	{
		get_tabhash(NULL, 1);
		if (data->home)
			free(data->home);
		if (data->oldpwd)
			free(data->oldpwd);
		free(data->line);
		freetab(data->args);
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
	else if (checklineok(data, data->args) != -1)
			return ;
	else if (ft_strcmp(data->args[0], "export") == 0)
		insertthetmp(data);
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
