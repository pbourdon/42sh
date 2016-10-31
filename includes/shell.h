/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 18:03:28 by pguzman           #+#    #+#             */
/*   Updated: 2016/10/22 10:29:31 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

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

typedef struct			s_lfd
{
	int					fd;
	int					open;
	int					read;
	int					write;
	struct s_lfd		*next;
}						t_lfd;

typedef struct			s_lredi
{
	char				*str;
	int					redi;
	struct s_lredi		*next;
}						t_lredi;

typedef struct			s_node
{
	char				*data;
	struct s_node		*p_prev;
	struct s_node		*p_next;
}						t_node;

typedef struct			s_dlist
{
	struct s_node		*p_tail;
	struct s_node		*p_head;
}						t_dlist;

typedef struct			s_liste2
{
	char				**tabb;
	t_lredi				*redir;
	t_lfd				*fd;
	pid_t				pid;
	int					pfd[2];
	struct s_liste2		*next;
}						t_liste2;

typedef struct			s_larg
{
	char				**tabb;
	struct s_larg		*next;
	struct s_redi		*redi;
}						t_larg;

typedef struct			s_redi
{
	int					redi;
	char				*agreg;
	struct s_redi		*next;
}						t_redi;

typedef struct			s_read
{
	int					limit;
	char				*prompt;
	int					secure;
	int					r;
	int					timeout;
	int					changed_fd;
}						t_read;

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
	struct s_history	*prev;
}						t_history;

typedef struct			s_hist_cont
{
	struct s_history	*hist;
	struct s_hist_cont	*next;
}						t_hist_cont;

typedef struct			s_liste
{
	char				*arg;
	struct s_liste		*next;
}						t_liste;

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
	int					shell_fd_0;
	struct s_term		term_reset;
	struct s_liste		*tab_lst;
	int					tab_lvl;
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
	char				*binpath;
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
	int					d;
	char				**builttab;
	char				**cur_env;
	int					binreturn;
	char				*forcd;
	int					exit;
	char				*exit_line;
	int					okchev;
	char				*tmpagreg;
	char				*avredi;
	struct s_builtin	*built;
	struct s_hist_cont	*hist_cont;
	struct s_tk			*l;
	struct s_larg		*argli;
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

typedef struct			s_builtin
{
	char				*str;
	void				(*blt)(struct s_data *data);
}						t_builtin;

char					*get_key_value2(char *key, char **env);
char					*get_key_value(char *key, char **env);
void					check_comp_norm(char *buffer);
t_liste					*get_next(t_liste *list, char *str);
int						print_padded_list(t_liste *list, int col, int max);
void					set_cur_end_word(char *cmd, int b_word);
int						get_max_and_close_circular_chainlist(t_liste *list);
void					print_nd_reset_cursor(t_liste *list, int cp);
int						space_nbr(char *str);
void					replace_cmd_cur_word(char *path, char *cmd, int i);
t_liste					*get_list_of_bin_completion(char *path);
t_liste					*get_list_of_file_completion(char *path);
t_liste					*get_list_completion(char *cmd, int i);
void					press_tab_key(void);
char					**init_fill_tab(char **tabhash, char *path, int res);
void					hash_refresh(t_data *data);
void					wait_all_pid(t_data *data);
char					*search_var(char *str, t_data *data, int i, int q);
char					*search_tild(char *str, t_data *data, int i, int q);
int						search_nb_pipe(t_tk *tk);
void					design_to_exec(t_data *data, t_liste2 *cur);
void					built_or_launch(t_data *data);
void					send_error(t_data *data);
int						builtin_check1(t_data *data);
char					**get_arg(t_tk **tk, char **tabb);
t_lfd					*init_fd(t_lfd *fd, t_lfd *base);
t_liste2				*final_list(t_liste2 *dest, t_tk *tk, int nb_pipe);
void					sub_split_norm_norm(char **cmd, t_tk *cur, int i);
void					sub_sub_split_norm(char **cmd, t_tk *cur, int i);
void					free_all_liste(t_liste2 **l);
void					redi_loop(t_liste2 *l, t_lredi *liste, t_data *data);
void					stock_fd(t_lfd *l, int fd, int t);
void					search_close_fd(t_liste2 *l, int df);
void					heredoc_to_stdin(t_liste2 *l, t_history *hist, \
						t_history *t);
void					free_heredoc(t_history *hist);
int						check_if_its_agreg(char *str);
void					to_handle_agreg(t_liste2 *l, t_lredi *liste);
void					to_to_handle_heredoc(t_liste2 *l, t_lredi *liste, \
		t_data *data);
void					to_main_fork_redirection_dbl(t_liste2 *l, \
		t_lredi *liste);
void					to_main_fork_redirection2(t_liste2 *l, t_lredi *liste);
void					to_main_fork_redirection(t_liste2 *l, t_lredi *liste);
void					stock_all_heredoc(t_data *data, t_liste2 *l);
void					free_all(t_data *data, t_liste2 *liste);
void					exec_on_env(t_data *data);
void					env_phase_2(t_data *data, int e);
void					p_or_e_choice(t_data *data, char **tabb, int i);
char					**get_env_nd_var(char **tabb, char **env);
char					**get_var(char **tabb);
int						env_error(char **tabb);
t_history				*hist_stock(char *line, t_history *n, \
		t_history *p, t_history *history);
int						export_no_pipe(t_data *data);
void					export_on_pipe(t_data *data);
void					builtin_echo(char *str);
char					*cdiftwo(t_data *data);
void					cdcall2(t_data *data, char *str);
void					deletefromenv(t_data *data, int k, int o);
void					free_new_env(char **env);
void					builtin_no_pipe(t_data *data);
int						is_a_builtin(char *str);
void					print_or_exec(t_data *data);
void					to_set_opwd(t_data *data);
void					to_set_pwd(t_data *data);
void					free_liste2(t_liste2 *l);
void					exit_on_pipe(t_data *data, char **tabb);
void					exit_no_pipe(t_data *data, char **tabb);
t_tk					*nsplit_on_inib(char *str);
void					create_command(char *command, t_liste2 *liste);
void					add_arg_to_history(t_data *data);
void					add_to_history(t_history *his, char *shell_line);
int						check_syntax(char **command);
int						ft_get_lenght_list(t_history *history);
int						append_to_list(void);
void					append_to_file(void);
void					design_to_start_string(t_data *data, char *target,\
		int find, t_liste2 *liste);
void					design_to_string(t_data *data, char *target, int find,\
		t_liste2 *liste);
void					show_helper_history(void);
int						check_syntax_designator(t_data *data);
void					designator(t_data *data, t_liste2 *cur);
t_liste2				*createliste(void);
int						is_ctrl_d(char *buffer);
char					**shell_lvl(char **env, int z);
void					show_history_rev_until(char *nb);
void					show_history_rev(void);
void					dell_history(void);
int						parenthesis_closed(void);
void					movements_delete(int a);
char					**split_on_inib(char *str);
void					show_history_until(char *len);
void					show_history(void);
int						ft_strisdigit(char *str);
int						ft_strlen_inib(char *str, int quote, int inib, int wrd);
char					quote_norm(int inib, char quote, char c);
void					history(t_data *data);
int						add_token(char *str);
t_liste					*create_list(void);
void					launch_main_fork(t_data *data);
int						is_a_word(int quote, int inib, char c);
void					free_tree(t_tree *tree);
int						switch_case(t_tk *ptr, int nb_redir, int nb_redir2);
void					free_first_list(t_tk *ptr);
void					free_list(t_liste *ptr);
void					arg_to_list(t_liste *liste, t_tree *tree);
t_liste					*create_list();
char					*ft_strcpy_inib(char *dest, char *str, int i, int j);
t_liste					*del_last_null_arg(t_liste *liste);
t_tree					*to_tree(t_tree *tree, t_tk *tk, int prio, char *str);
void					go_free(char *cwd, char *hostname, char *curtime);
void					aff(t_tree *tree);
t_tk					*good_order(t_tk *ptr, t_tk *prev, t_tk *base);
int						sub_split_on_spec(char **cmd, char **ptr);
int						is_a_spec2(char *str, char c);
void					fill_the_main_liste(t_data *data);
char					*free_space(char *str, int quote, int d, int i);
char					*replace_rest_of_space(char *ptr, int len);
char					*erase_first_space(char *line);
int						is_a_spec(char c);
int						check_list(t_tk *liste);
int						check_list_2(t_liste *liste);
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
void					fill_the_agreg_liste(t_data *data);
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
void					forkall(t_data *data, int status);
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
int						main_init(t_term *term);
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
int						ft_exit_error(t_data *data, int *out);
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
int						mainredi(t_data *data, int i);
int						doubleredichieh(t_data *data, t_liste2 *liste, int i);
int						execveremix(t_data *data);
int						createthetab(t_data *data);
char					*decoupe1(char *str);
char					*decoupe2(char *str);
int						helpall2(t_data *data, t_liste2 *liste);
int						mainpipehelp2(t_data *data, t_liste2 *liste);
void					childhelp(t_data *data, t_liste2 *liste, int pfd[2]);
char					*ft_str2join(char *bar, char *yoo, char *foo);
int						optchev(t_data *data);
t_liste2				*createliste(void);
void					set_open_adressing(char **tabhash, int res, char *path);
void					argliste(t_data *data);
int						hash_bin(char *bin);
void					freeliste(t_liste2 *liste);
char					*ft_chrbin(char *path);
int						checkagred(char *str, int i, int o);
char					**createtab(t_data *data, int i);
void					printtab(char **tabb);
void					help_dbl(t_data *data, int i, t_liste2 *liste, int fd);
int						mainpipehelp(t_data *data, t_liste2 *liste);
int						mainpipe(t_data *data, t_liste2 *liste);
void					rediboucle(t_liste2 *liste);
void					helpmainpipehelp2(t_data *data, t_liste2 *liste, int k);
void					delete_selection_if_other_than_option(char *buffer);
void					ft_reset_term();
void					go_home();
void					sig_handler_ctrl_c(int a);
int						countstr(char *str, int i);
int						agreve(t_data *data, t_liste2 *liste);
int						createbinpath(t_data *data, int n);
int						hulppls(t_data *data, t_liste2 *liste, int pfd[2]);
void					parsecommand(t_data *data, t_liste *liste);
int						mainpipecond(t_data *data, t_liste2 *liste);
char					*get_bin(char *bin);
void					update_shell_line_original(void);
char					**get_tabhash(char **new, int b);
void					free_tabhash(void);
void					init_hashtab(t_data *data, char **env, int i);
int						checklineok(t_data *data, char **tabb);
void					insertthetmp(t_data *data);
int						intb2(t_data *data, char *str, char *dst, char **tabb);
void					helpagreve(t_data *data, int a, int b, t_liste2 *liste);
void					helpagreve2(t_data *data, t_liste2 *liste);
char					*secondpartequal(char *str);
char					*firstpartequal(char *str);
char					**freshnewtab(t_data *data, char *dst, char *dst2);
int						alreadyin(t_data *data, char *str);
int						stringforcd(t_data *data);
int						cdendargs(t_data *data);
int						movecd(t_data *data);
int						sub_parsecommand2(t_data *data);
void					sub_parsecommand(t_data *data, int i);
void					free_liste2(t_liste2 *ptr);
void					free_list2(t_liste *ptr);
int						optchev2(t_data *data, int i, char *str);
int						is_tab(char *buffer);
int						isanum(char *str);
int						get_pos_l(void);
t_shell					g_shell;
t_cursor				g_cursor;
void					callecho(char **args);
void					main_fork(t_data *data, t_liste2 *liste);
void					movements_delete2(int a);
int						ft_init_verif(int a, char *b);
int						ft_strchr_i(char *str, char c);
int						get_pos_jump(void);
int						get_pos_backv2(void);
int						get_n_line2(void);
int						get_n_line(void);
int						aux1(void);
int						since_last(int k);
void					sig_handler22(int sign);
void					sig_handler2(int sign);
char					*get_user_name(char **env);
int						is_there_a_path(char **env);
char					*ft_check_designat(char *command, int *fake,
						int index, int index2);
char					*ft_error_event_char(char *command, int display);
char					*ft_error_event_char2(char *command, int di, char *str);
char					*ft_replace_designator_norm(int number, char *command,
						int display);
char					*ft_replace_designator_rev(int number, char *command,
						int display);
char					*ft_replace_designator4(char *command, char *command2,
						int display);
char					*ft_replace_designator5(char *command, char *command2,
						int display);
char					*ft_replace_designator6(char *command);
char					*ft_strdup_special(char *src, char *dest);
char					*ft_last_ope(char *final, int display);
int						ft_adv_co(char *command, int index);
void					ft_read(t_data *data);
t_dlist					*ft_add_data(t_dlist *p_list, char *var);
t_dlist					*dlist_append(t_dlist *p_list, char *variable);
t_dlist					*dlist_prepend(t_dlist *p_list, char *variable);
void					dlist_delete(t_dlist **p_list);
t_dlist					*nik_the_norm2(t_dlist *p_list, t_node *p_new, int i);
t_dlist					*nik_the_norm3(t_dlist *p_list, t_node *p_new, int i);
t_dlist					*ins_avant(t_dlist *liste, char *variable, \
						t_node *courant, int pos);
t_dlist					*dlist_new(t_dlist *p_new);
int						ft_display_list(t_dlist *p_list);
void					ft_delete_list(t_dlist **p_list);
void					ft_put_error_read(void);
char					*ft_get_str_from_tab(char **tabb, int i, int a, int d);
t_dlist					*ft_create_list_read(t_data *data, \
						t_dlist *alpha, int pos);

#endif
