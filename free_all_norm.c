/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newredi11.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 23:06:44 by cmichaud          #+#    #+#             */
/*   Updated: 2016/09/29 13:24:07 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	free_all_tok(t_tk **tok)
{
	t_tk *tk;
	t_tk *tmp;

	tk = *tok;
	while (tk)
	{
		tmp = tk->next;
		ft_memdel((void **)&tk->arg);
		ft_memdel((void **)&tk);
		tk = tmp;
	}
	tok = NULL;
}

void	free_all_tabb(char ***t)
{
	char	**tabb;
	int		i;

	i = -1;
	tabb = *t;
	while (tabb[++i])
		ft_memdel((void **)&tabb[i]);
	ft_memdel((void **)&tabb);
	t = NULL;
}

void	free_all_heredoc(t_hist_cont **h_c)
{
	t_hist_cont		*hc;
	t_hist_cont		*tp;
	t_history		*mp;
	t_history		*tm;

	hc = *h_c;
	tp = hc;
	while (hc)
	{
		tp = hc->next;
		mp = hc->hist;
		while (mp)
		{
			tm = mp->next;
			ft_memdel((void **)&mp->str);
			ft_memdel((void **)&mp);
			mp = tm;
		}
		ft_memdel((void **)&hc);
		hc = tp;
	}
	h_c = NULL;
}

void	free_all(t_data *data, t_liste2 *liste)
{
	if (liste)
		free_all_liste(&liste);
	data->liste = NULL;
	if (data->args)
		free_all_tabb(&data->args);
	data->args = NULL;
	if (data->tabb)
		free_all_tabb(&data->tabb);
	data->tabb = NULL;
	if (data->l)
		free_all_tok(&data->l);
	data->l = NULL;
	if (data->hist_cont)
		free_all_heredoc(&data->hist_cont);
	data->hist_cont = NULL;
	if (data->line)
		ft_memdel((void **)&data->line);
}
