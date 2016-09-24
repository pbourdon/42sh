/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_main_fork.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 17:03:20 by cmichaud          #+#    #+#             */
/*   Updated: 2016/09/24 17:11:53 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		redi_loop(t_liste2 *l, t_lredi *liste, t_data *data)
{
	t_lredi *tmp;

	tmp = liste;
	while (tmp)
	{
		if (check_if_its_agreg(tmp->str) == 1)
			to_handle_agreg(l, tmp);
		if (tmp->redi == 4)
			to_to_handle_heredoc(l, tmp, data);
		if (tmp->redi == 1)
			to_main_fork_redirection(l, tmp);
		if (tmp->redi == 2)
			to_main_fork_redirection_dbl(l, tmp);
		if (tmp->redi == 3)
			to_main_fork_redirection2(l, tmp);
		tmp = tmp->next;
	}
}

int			main_fork_exec_rediclose(t_data *data, t_liste2 *liste,\
									int pfd[2], int i)
{
	if (i == 1)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
	}
	data->args = newtab(liste->tabb);
	redi_loop(liste, liste->redir, data);
	freetab(data->args);
	data->args = newtab(liste->tabb);
	execveremix(data, liste);
	return (1);
}

void		wait_all_pid(t_data *data)
{
	t_liste2	*liste;
	int			status;

	liste = data->liste;
	status = 0;
	while (liste)
	{
		if (liste->pid == 0)
			exit(255);
		else
			waitpid(liste->pid, &status, 0);
		liste = liste->next;
	}
	if (status)
		exit(1);
	exit(0);
}

void		main_fork(t_data *data, t_liste2 *liste)
{
	if ((liste->next == NULL) && ((liste->pid = fork()) == 0))
		main_fork_exec_rediclose(data, liste, NULL, 2);
	else if (liste->next != NULL)
	{
		pipe(liste->pfd);
		if ((liste->pid = fork()) == 0)
			main_fork_exec_rediclose(data, liste, liste->pfd, 1);
		close(liste->pfd[1]);
		dup2(liste->pfd[0], 0);
		main_fork(data, liste->next);
	}
	close(liste->pfd[1]);
	close(liste->pfd[0]);
	wait_all_pid(data);
}

void		launch_main_fork(t_data *data)
{
	pid_t	father;
	int		status;

	status = 0;
	data->hist_cont = NULL;
	stock_all_heredoc(data, data->liste);
	if ((!data->liste->next && is_a_builtin(data->liste->tabb[0]))
		|| checklineok(data, data->liste->tabb) != -1)
	{
		builtin_no_pipe(data);
		free_all(data, data->liste);
		return ;
	}
	else if ((father = fork()) == 0)
		main_fork(data, data->liste);
	else
		wait(&status);
	data->binreturn = status;
	free_all(data, data->liste);
}
