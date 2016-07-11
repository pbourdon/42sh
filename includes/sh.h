/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 14:06:40 by bde-maze          #+#    #+#             */
/*   Updated: 2016/07/10 14:06:41 by bde-maze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "libft.h"
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <signal.h>

typedef struct			s_liste
{
	int					end;
	char				*data;
	struct	s_liste		*next;
	struct	s_liste		*prev;
}						t_liste;

typedef struct			s_env
{
	t_liste				*list;
}						t_env;

#endif

