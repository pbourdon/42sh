/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 21:10:55 by cmichaud          #+#    #+#             */
/*   Updated: 2016/09/21 18:14:33 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	callecho(char **args)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		builtin_echo(args[i]);
		if (args[i] + 1)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}
