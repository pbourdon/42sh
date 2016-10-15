/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_event.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourdon <pbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 18:44:42 by pbourdon          #+#    #+#             */
/*   Updated: 2016/10/15 19:00:19 by pbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char	*ft_error_event_char(char *command)
{
	ft_putstr_fd("sh : ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": event not found", 2);
	return (NULL);
}
