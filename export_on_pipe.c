/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_on_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 20:43:05 by cmichaud          #+#    #+#             */
/*   Updated: 2016/10/18 15:31:09 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void		print_export(t_data *data)
{
	char	*tmp;
	int		i;

	i = -1;
	ft_putendl("titi");
	while (data->env && data->env[++i])
	{
		ft_putstr("export ");
		tmp = ft_strchr(data->env[i], '=');
		*tmp = 0;
		ft_putstr(data->env[i]);
		if (*(tmp + 1))
		{
			write(1, "=\"", 2);
			ft_putstr(tmp + 1);
			write(1, "\"\n", 2);
		}
		else
			write(1, "\n", 1);
		*tmp = '=';
	}
}

void		export_on_pipe(t_data *data)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!data->args)
		data->args = data->liste->tabb;
	if (!data->args[1])
	{
		print_export(data);
		exit((data->binreturn = 0));
	}
	while (data->args[++i])
	{
		if ((tmp = ft_strchr(data->args[i], '=')) && tmp == data->args[i])
		{
			ft_putstr_fd(data->args[i], 2);
			ft_putendl_fd(" not a valid identifier", 2);
			exit((data->binreturn = 1));
		}
	}
}

int			export_no_pipe(t_data *data)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!data->args)
		data->args = data->liste->tabb;
	if (!data->args[1])
	{
		print_export(data);
		return ((data->binreturn = 0));
	}
	while (data->args[++i])
	{
		if ((tmp = ft_strchr(data->args[i], '=')) && tmp == data->args[i])
		{
			ft_putstr_fd(data->args[i], 2);
			ft_putendl_fd(" not a valid identifier", 2);
			return ((data->binreturn = 1));
		}
	}
	return (2);
}
