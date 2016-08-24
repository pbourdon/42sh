/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <cmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 18:33:29 by cmichaud          #+#    #+#             */
/*   Updated: 2016/08/23 19:48:06 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <termios.h>
# include <term.h>
# include <time.h>
# include <unistd.h>
# include <stdlib.h>

# define OTHER 0
# define AGGR 1
# define BACK 2
# define REDDIR 3
# define OPBI 4
# define SEPP 5

# define NONE 0
# define WEAK 1
# define STRONG 2
# define ALONE 3

# define INPUT 0
# define OUTPUT 1

typedef struct			s_liste2
{
	char				**tabich;
	int					redi;
	struct s_liste2		*next;
}						t_liste2;

typedef struct			s_term
{
	char				*term_name;
	struct termios		term;
	struct termios		term_copy;

}						t_term;

typedef struct			s_history
{
	char				*str;
	struct s_history	*next;
}						t_history;

typedef struct			s_shell
{
	int					shell_status;
	int					backslash_index;
	int					length_line;
	int					shell_win_size;
	char				*shell_line_original;
	int					history_index;
	int					shell_backslash_level;
	int					last_backslash;
	char				*shell_line;
	struct s_history	*history;
	int					selected_start;
	int					selected_end;
	char				*selected_copy;
	int					shell_heredoc;
	int					size;
}						t_shell;

typedef struct			s_cursor
{
	int					position_x_abs;
	int					position_y_abs;
	int					position_x_rel;
	int					position_y_rel;
	int					position_line;
}						t_cursor;

typedef struct			s_data
{
	char				*line;
	char				*path;
	char				**allp;
	char				*bin;
	char				*home;
	char				*pwd;
	char				*oldpwd;
	char				*voldpwd;
	char				**tabb;
	char				**env;
	char				**args;
	char				**oldenv;
	int					dspam;
	int					envi;
	int					fona;
	int					turn;
	char				**tabchev;
	char				**oldtbe;
	int					posi;
	char				**builttab;
	struct s_liste2		*liste;
}						t_data;

typedef struct			s_tree
{
	char				*arg;
	int					tk;
	struct s_tree		*left;
	struct s_tree		*right;
}						t_tree;

typedef struct			s_tk
{
	int					inib;
	int					tube;
	int					tk;
	char				*arg;
	struct s_tk			*next;
}						t_tk;

typedef struct			s_liste
{
	char				*arg;
	struct s_liste		*next;
}						t_liste;

int						add_token(char *str);
t_liste					*create_list(void);
void					free_tree(t_tree *tree);
int						switch_case(t_tk *ptr, int nb_redir, int nb_redir2);
void					free_first_list(t_tk *ptr);
void					free_list(t_liste *ptr);
void					arg_to_list(t_liste *liste, t_tree *tree);
t_liste					*create_list();
t_liste					*del_last_null_arg(t_liste *liste);
t_tree					*to_tree(t_tree *tree, t_tk *tk, int prio, char *str);
void					go_free(char *cwd, char *hostname, char *curtime);
void					aff(t_tree *tree);
t_tk					*good_order(t_tk *ptr, t_tk *prev, t_tk *base);
int						sub_split_on_spec(char **cmd, char **ptr);
int						is_a_spec2(char *str, char c);
char					*free_space(char *str, int quote, int d, int i);
char					*replace_rest_of_space(char *ptr, int len);
char					*erase_first_space(char *line);
int						is_a_spec(char c);
int						check_list(t_tk *liste, t_tk *ptr, int ret, int nb_agg);
t_tk					*analyse_and_stock(char **ptr, char **cmd, t_tk **base);
t_tk					*to_list(char *cmd, int i);
t_tk					*find_space(char *cmd, t_tk *tk, int inib, char quote);
t_tk					*split_on(char **ptr, char **cmd, t_tk **bs, t_tk *cur);
void					prompt_line(char **env);
void					writeonwhile(void);
void					catchpath(t_data *data);
char					**changeargs(char **tabb, t_data *data);
void					callenvtool(t_data *data, char **tabb);
char					**printifenv(char **tabb, char *str);
int						alreadyexist(char **tabb, char *str);
int						ft_strlenremix(char *str);
char					*getpwd(void);
char					**newtab(char **tabb);
void					freedata(char *str, t_data *data);
int						errcd(t_data *data);
void					freedata(char *str, t_data *data);
char					**ft_initenv(char **env);
void					callunsetenv(t_data *data);
void					changepwdenv(t_data *data);
void					argsifenv(t_data *data, int n);
char					*transformtab(char *str);
void					changepathintab(t_data *data);
char					*withoutspace(char *str);
char					*joincd(char *str, t_data *data);
void					gethome(t_data *data);
int						createbinpath2(t_data *data, char *str);
void					cdcall(t_data *data);
int						rognagestring(char *str, char *str2);
void					callsetenv(t_data *data);
char					**setenvifexist(t_data *data, int a);
char					*fillmytab(char *str);
void					freetab2(t_data *data);
void					printab(char **tabb);
int						alreadyexist(char **tabb, char *str);
int						ft_strlentab(char **tabb);
char					**setenvifdontexist(t_data *data, int a);
void					errorbinary(t_data *data, char *str);
void					callallenv(t_data *data);
void					printenv(t_data *data);
void					callenv(t_data *data);
void					forkall(t_data *data);
int						readgnl(t_data *data, char *str);
void					freetab(char **tabb);
int						shell_loop(t_term *term, t_data *data, char **env);
void					shell_init(void);
char					**shell_env_copy(char *envp[]);
void					shell_shlvl(char ***cp);
int						shell_var_exists(char **cp, const char *name, int len);
int						shell_envlen(char **envp);
char					**shell_parsing(char *line);
int						shell_builtins(char **s, char ***cp, char *builtin[5]);
void					main_init(t_term *term);
int						tputs_putchar(int c);
int						shterm_listen(t_term *term);
void					shell_listening_char();
int						term_init(t_term *term);
int						is_delete_key(char *buffer);
int						is_direction_key(char *buffer);
int						is_backspace_key(char *buffer);
int						is_home_key(char *buffer);
int						is_end_key(char *buffer);
int						is_down_key(char *buffer);
int						is_up_key(char *buffer);
int						is_left_key(char *buffer);
int						is_right_key(char *buffer);
int						is_enter_key(char *buffer);
int						is_option_c(char *buffer);
int						is_option_v(char *buffer);
int						is_option_right(char *buffer);
int						is_option_left(char *buffer);
int						is_printable_char(char *buffer);
int						is_eot(char *buffer);
int						is_option_key(char *buffer);
void					press_option_key(char *buffer);
void					press_direction_key(char *buffer);
void					press_backspace_key();
void					press_delete_key();
void					press_up_key();
void					press_down_key();
void					press_left_key();
void					press_right_key();
void					press_printable_char(char *buffer);
void					press_home_key();
void					press_end_key();
int						press_enter_key();
void					press_option_c();
void					press_option_v();
void					press_option_left();
void					press_option_right();
char					*del_from_arr(char *str, int i);
void					go_right();
void					go_left();
int						ft_exit_error(char **s);
int						ft_isnumber(char *s);
void					ft_tabdel(char ***tb);
char					**ft_tab_trim(char **s);
char					**ft_strsplit2(char const *s);
int						ft_isblanck(char c);
void					cursor_init();
void					line_init();
void					add_to_history(t_history *his, char *str);
t_history				*double_left(char *fin);
unsigned int			fsize(const char *filename);
char					**get_history();
char					*add_to_array(char *str, char c, int i, int len);
int						ft_putstr_i(char *str, int i);
void					move_cursor_right();
void					move_cursor_left();
void					print_cursor_fd_2();
void					print_shell_fd_2();
void					print_buffer(char *buffer);
void					press_shift_direction_key(char *buffer);
int						get_next_word_after(char *str, int c);
int						is_shift_direction_key(char *buffer);
void					press_shift_left();
void					press_shift_right();
void					press_shift_up();
void					press_shift_down();
int						get_next_word_before(char *str, int c);
void					add_jump();
void					delete_last_backslash();
void					replace_shell_line(char *str);
void					replace_shell_backslash_line();
int						ft_strlend(char **str);
int						listen(char *buffer);
int						is_shift_up(char buffer5);
int						is_shift_down(char buffer5);
int						is_shift_right(char buffer5);
int						is_shift_left(char buffer5);
char					*get_history_i(int i);
int						get_history_length();
void					sig_handler(int a);
void					sig_ctrl_d();
void					update_cursor();
void					prepare_to_listen(char buffer[9]);
int						shterm_listen(t_term *term);
char					*extract_str(char *str, int a, int b);
int						ifitsredi(t_data *data);
int						mainredi(t_data *data);
int						doubleredichieh(t_data *data, t_liste2 *liste);
int						execveremix(t_data *data);
int						createthetab(t_data *data);
char					*decoupe1(char *str);
char					*decoupe2(char *str);
int						helpall2(t_data *data, t_liste2 *liste);
int						mainpipehelp2(t_data *data, t_liste2 *liste);
void					childhelp(t_data *data, t_liste2 *liste, int pfd[2]);
int						optchev(t_data *data);
t_liste2				*createliste(void);
void					argliste(t_data *data);
void					freeliste(t_liste2 *liste);
int						checkagred(char *str);
char					**createtab(t_data *data, int i);
void					printtab(char **tabb);
void					help_dbl(t_data *data, int i, t_liste2 *liste, int fd);
int						mainpipehelp(t_data *data, t_liste2 *liste);
int						mainpipe(t_data *data, t_liste2 *liste);
void					rediboucle(t_liste2 *liste);
void					helpmainpipehelp2(t_data *data, t_liste2 *liste, int k);
int						ft_reset_term(struct termios term);
void					sig_handler_ctrl_c(int a);
int						countstr(char *str, int i);
int						agreve(t_data *data, t_liste2 *liste);
int						createbinpath(t_data *data, int n);
int						hulppls(t_data *data, t_liste2 *liste, int pfd[2]);
void					parsecommand(t_data *data, t_liste *liste);
int						mainpipecond(t_data *data, t_liste2 *liste);
char					*get_bin(char *bin);
char					**get_tabhash(char **new, int b);
void					free_tabhash(void);
void					init_hashtab(char **env);
int						checklineok(t_data *data, char **tabb);
int						insertthetmp(t_data *data);
int		alreadyintb2(t_data *data, char *str, char *dst, char **tabb);
char	*secondpartequal(char *str);
char	*firstpartequal(char *str);
char	**freshnewtab(t_data *data, char *dst, char *dst2);
int		alreadyin(t_data *data, char *str);

t_shell					g_shell;
t_cursor				g_cursor;

#endif
