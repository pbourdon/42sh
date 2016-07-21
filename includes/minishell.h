/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlouar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 16:58:19 by hlouar            #+#    #+#             */
/*   Updated: 2016/05/23 10:22:18 by hlouar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "../ft_printf/includes/ft_printf.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

# define OTHER 0
# define AGGR 1
# define REDDIR 2
# define SEPP 3
# define OPBI 4
# define BACK 5

# define NONE 0
# define WEAK 1
# define STRONG 2
# define ALONE 3

# define INPUT 0
# define OUTPUT 1



typedef struct		s_data
{
	char			*line;
	char			*path;
	char			**allp;
	char			*bin;
	char			*home;
	char			*pwd;
	char			*oldpwd;
	char			*voldpwd;
	char			**tab;
	char			**env;
	char			**args;
	char			**oldenv;
	int				dspam;
	int				envi;
	int				fona;
	int				turn;
}					t_data;

typedef struct		s_token
{
	int				inib; // non: 0; weak: 1; strong: 2; unique: 3
	int				tube; // input or output
	int				token; // ohter: 0; aggr: 1; reddir: 2; sepp: 3; opbi:4; back:5;
	char			*arg;
	struct s_token	*next;
}					t_token;


int					is_a_spec(char c);
t_token				*to_list(char *cmd);
t_token				*split_on_spec(char **ptr, char **cmd, t_token **base);
int					check_list(t_token *liste);



void				writeonwhile(void);
void				catchpath(t_data *data);
char				**changeargs(char **tab, t_data *data);
void				callenvtool(t_data *data, char **tab);
char				**printifenv(char **tab, char *str);
int					alreadyexist(char **tab, char *str);
int					ft_strlenremix(char *str);
char				*getpwd(void);
char				**newtab(char **tab);
void				freedata(char *str, t_data *data);
int					errcd(t_data *data);
void				freedata(char *str, t_data *data);
char				**ft_initenv(char **env);
void				callunsetenv(t_data *data);
void				changepwdenv(t_data *data);
void				argsifenv(t_data *data, int n);
char				*transformtab(char *str);
void				changepathintab(t_data *data);
char				*withoutspace(char *str);
char				*joincd(char *str, t_data *data);
void				gethome(t_data *data);
int					createbinpath2(t_data *data, char *str);
void				cdcall(t_data *data);
int					rognagestring(char *str, char *str2);
void				callsetenv(t_data *data);
char				**setenvifexist(t_data *data, int a);
char				*fillmytab(char *str);
void				freetab2(t_data *data);
void				printab(char **tab);
int					alreadyexist(char **tab, char *str);
int					ft_strlentab(char **tab);
char				**setenvifdontexist(t_data *data, int a);
int					createbinpath(t_data *data);
void				errorbinary(t_data *data, char *str);
void				callallenv(t_data *data);
void				printenv(t_data *data);
void				callenv(t_data *data);
void				forkall(t_data *data);
int					readgnl(t_data *data);
void				freetab(char **tab);

#endif
