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

typedef struct			s_node
{
	char				*str;
	struct s_node		*prev;
	struct s_node		*next;
}						t_node;

typedef struct			s_liste
{
	struct s_node		*head;
	struct s_node		*tail;
}						t_liste;

typedef struct 			s_env
{
	struct s_liste		*list;
}						t_env;

#endif

