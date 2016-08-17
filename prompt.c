/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 18:03:07 by bde-maze          #+#    #+#             */
/*   Updated: 2016/05/04 18:03:22 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char			*get_pwd(void)
{
	char		*cwd;
	char		*tmp;
	int			len;

	len = 0;
	cwd = ft_memalloc(sizeof(char) * 1024);
	cwd = getcwd(cwd, 1024);
	if (cwd == NULL)
		return (NULL);
	len = ft_strlen(cwd);
	tmp = ft_memalloc(sizeof(char) * len + 1);
	tmp = ft_strncpy(tmp, cwd, len);
	free(cwd);
	return (tmp);
}

char			*ntime(void)
{
	char		*tmp;
	int			len;
	int			i;
	char		*curtime;
	time_t		ntime;

	i = 0;
	len = 0;
	ntime = time(NULL);
	curtime = ctime(&ntime);
	while (i < 11)
	{
		curtime++;
		i++;
	}
	len = ft_strlen(curtime);
	len = len - 5;
	tmp = ft_memalloc(sizeof(char) * len + 1);
	tmp = ft_strncpy(tmp, curtime, len);
	return (tmp);
}

char			*save_post(char *hostname)
{
	int			len;
	char		*tmp;

	len = ft_strlen(hostname);
	len = len - 6;
	tmp = ft_memalloc(sizeof(char) * len + 1);
	tmp = ft_strncpy(tmp, hostname, len);
	return (tmp);
}

void			go_free(char *cwd, char *prompt, char *hostname, char *curtime)
{
	free(cwd);
	free(prompt);
	free(hostname);
	free(curtime);
}

void			prompt_line(void)
{
	char		*cwd;
	char		*prompt;
	char		*hostname;
	char		*curtime;

	hostname = ft_memalloc(sizeof(char) * 1024);
	hostname[1023] = '\0';
	gethostname(hostname, 1000);
	hostname = save_post(hostname);
	hostname = ft_strjoin("bde-maze@", hostname);
	curtime = ntime();
	curtime = ft_strjoin(" ", curtime);
	cwd = get_pwd();
	if (cwd == NULL)
		cwd = ft_strdup("#error#");
	prompt = ft_strjoin(hostname, curtime);
	prompt = ft_strjoin(prompt, cwd);
	ft_putstr("\033[35m");
	ft_putstr(hostname);
	ft_putstr(" \033[36m-");
	ft_putstr(curtime);
	ft_putstr("- \033[32m");
	ft_putendl(cwd);
	ft_putstr("\033[32m-> % \033[39m ");
	go_free(cwd, prompt, hostname, curtime);
}
