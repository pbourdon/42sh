Binary file 21sh matches
Makefile:		history_show_func.c \
Makefile:		history_option.c \
Makefile:		history_tools.c \
Makefile:		history.c \
Makefile:		history_norm_tool.c \
add_letter.c:int		get_history_length(void)
add_letter.c:	t_history	*history;
add_letter.c:	history = g_shell.history;
add_letter.c:	if (history->str)
add_letter.c:	while (history->next)
add_letter.c:		history = history->next;
builtin_handler.c:		!ft_strcmp(str, "history"))
designator.c:	t_history	*history;
designator.c:	i = g_shell.history_index;
designator.c:	history = g_shell.history;
designator.c:	if (!history->str)
designator.c:	while (history->next)
designator.c:		history = history->next;
designator.c:	while (history && i-- > len)
designator.c:		history = history->prev;
designator.c:	if (!history || history->str)
designator.c:	t_history	*history;
designator.c:	history = g_shell.history;
designator.c:	if (!history->str)
designator.c:	while (i < index && history)
designator.c:		history = history->next;
designator.c:	if (!history || history->str)
designator_exec.c:	t_history		*history;
designator_exec.c:	history = g_shell.history;
designator_exec.c:	ft_putendl(history->str);
designator_exec.c:	create_command(history->str, cur);
designator_string.c:	t_history	*history;
designator_string.c:	history = g_shell.history;
designator_string.c:	if (!history->str)
designator_string.c:	while (history)
designator_string.c:		command = ft_strsplit(history->str, ' ');
designator_string.c:		history = history->next;
designator_string.c:		sub_design_to_string(data, history->str, liste);
designator_string.c:	t_history	*history;
designator_string.c:	history = g_shell.history;
designator_string.c:	if (!history->str)
designator_string.c:	while (history)
designator_string.c:		command = ft_strsplit(history->str, ' ');
designator_string.c:		history = history->next;
designator_string.c:		return (sub_design_to_string(data, history->str, liste));
free_all_norm.c:	t_history		*mp;
free_all_norm.c:	t_history		*tm;
ft_redirect4.c:	else if (!ft_strcmp(data->args[0], "history"))
ft_redirect4.c:		history(data);
ft_replace_designator.c:	t_history		*history;
ft_replace_designator.c:	history = g_shell.history;
ft_replace_designator.c:	if (!history->str)
ft_replace_designator.c:	while (i <= number && history)
ft_replace_designator.c:		history = history->next;
ft_replace_designator.c:	if (!history || !history->str)
ft_replace_designator.c:	return (history->str);
ft_replace_designator.c:	t_history		*history;
ft_replace_designator.c:	history = g_shell.history;
ft_replace_designator.c:	if (!history->str)
ft_replace_designator.c:	while (history->next)
ft_replace_designator.c:		history = history->next;
ft_replace_designator.c:	while (history && number-- > 0)
ft_replace_designator.c:		history = history->prev;
ft_replace_designator.c:	if (!history || !history->str)
ft_replace_designator.c:	return (history->str);
ft_replace_designator.c:	t_history		*history;
ft_replace_designator.c:	history = g_shell.history;
ft_replace_designator.c:	if (!history->str)
ft_replace_designator.c:	while (history->next)
ft_replace_designator.c:		history = history->next;
ft_replace_designator.c:	while (history && ft_strncmp(history->str, command, index))
ft_replace_designator.c:		history = history->prev;
ft_replace_designator.c:	if (!history || !history->str)
ft_replace_designator.c:	return (history->str);
ft_replace_designator.c:	t_history		*history;
ft_replace_designator.c:	history = g_shell.history;
ft_replace_designator.c:	if (!history->str)
ft_replace_designator.c:	while (history->next)
ft_replace_designator.c:		history = history->next;
ft_replace_designator.c:	while (history && ft_strstr(history->str, str) == NULL)
ft_replace_designator.c:		history = history->prev;
ft_replace_designator.c:	if (!history || !history->str)
ft_replace_designator.c:	return (history->str);
history.c:/*   history.c                                          :+:      :+:    :+:   */
history.c:	t_history	*history;
history.c:	t_history	*tmp;
history.c:	history = g_shell.history;
history.c:	while (history != NULL && i < offset)
history.c:		tmp = history->next;
history.c:		if (history->str)
history.c:			ft_strdel(&history->str);
history.c:		free(history);
history.c:		history = tmp;
history.c:	g_shell.history = history;
history.c:	if (history == NULL)
history.c:		free(history);
history.c:		g_shell.history = (t_history *)malloc(sizeof(t_history));
history.c:		g_shell.history->str = NULL;
history.c:		g_shell.history->next = NULL;
history.c:		g_shell.history->prev = NULL;
history.c:void			dell_history_offset(t_data *data, char *offset)
history.c:			real_offset >= ft_get_lenght_list(g_shell.history))
history.c:			ft_putstr("sh: history: ");
history.c:			ft_putendl(": history position out of range");
history.c:		ft_putendl("sh: history: -d: option requires an argument");
history.c:		show_helper_history();
history.c:			ft_putendl("sh: history: no history source file");
history.c:		add_arg_to_history(data);
history.c:		show_helper_history();
history.c:		ft_putendl("sh: history: cannot use more than one option");
history.c:		show_helper_history();
history.c:		dell_history();
history.c:		dell_history_offset(data, data->args[2]);
history.c:			show_history_rev();
history.c:			show_history_rev_until(data->args[2]);
history.c:void			history(t_data *data)
history.c:		show_helper_history();
history.c:		show_history();
history.c:			ft_putendl_fd("history : too many arguments", 2);
history.c:			show_history_until(data->args[1]);
history_norm_tool.c:/*   history_norm_tool.c                                :+:      :+:    :+:   */
history_norm_tool.c:t_history		*hist_stock(char *line, t_history *n,
history_norm_tool.c:							t_history *p, t_history *history)
history_norm_tool.c:	history->str = ft_strdup(line);
history_norm_tool.c:	history->prev = p;
history_norm_tool.c:	history->next = n;
history_norm_tool.c:	return (history);
history_option.c:/*   history_option.c                                   :+:      :+:    :+:   */
history_option.c:void			add_to_history(t_history *his, char *shell_line)
history_option.c:	t_history	*history;
history_option.c:	history = his;
history_option.c:	if (history->str == NULL)
history_option.c:		history->str = ft_strdup(shell_line);
history_option.c:		if (history->next)
history_option.c:			while (history->next)
history_option.c:				history = history->next;
history_option.c:		history->next = (t_history *)malloc(sizeof(t_history));
history_option.c:		history->next->str = ft_strdup(shell_line);
history_option.c:		history->next->prev = history;
history_option.c:		history->next->next = NULL;
history_option.c:	t_history	*history;
history_option.c:	t_history	*tmp;
history_option.c:	history = g_shell.history;
history_option.c:		history = hist_stock(line, NULL, NULL, history);
history_option.c:			history->next = (t_history *)malloc(sizeof(t_history));
history_option.c:			tmp = history;
history_option.c:			history = history->next;
history_option.c:			history = hist_stock(line, NULL, tmp, history);
history_option.c:	t_history	*tmp;
history_option.c:	out = open(".ftsh_history", O_RDWR);
history_option.c:	dell_history();
history_option.c:	tmp = g_shell.history;
history_option.c:void			add_arg_to_history(t_data *data)
history_option.c:		ft_putendl_fd("sh: history: give at least one argument", 2);
history_option.c:		show_helper_history();
history_option.c:		add_to_history(g_shell.history, data->args[i++]);
history_option.c:	t_history	*history;
history_option.c:	history = g_shell.history;
history_option.c:	if ((fd = open(".ftsh_history", O_WRONLY | O_TRUNC |
history_option.c:	while (history)
history_option.c:		ft_putendl_fd(history->str, fd);
history_option.c:		history = history->next;
history_show_func.c:/*   history_show_func.c                                :+:      :+:    :+:   */
history_show_func.c:void			dell_history(void)
history_show_func.c:	t_history	*history;
history_show_func.c:	t_history	*tmp;
history_show_func.c:	history = g_shell.history;
history_show_func.c:	while (history != NULL)
history_show_func.c:		tmp = history->next;
history_show_func.c:		if (history->str)
history_show_func.c:			ft_memdel((void **)&history->str);
history_show_func.c:		ft_memdel((void **)&history);
history_show_func.c:		history = tmp;
history_show_func.c:	g_shell.history = (t_history *)malloc(sizeof(t_history));
history_show_func.c:	g_shell.history->str = NULL;
history_show_func.c:	g_shell.history->next = NULL;
history_show_func.c:	g_shell.history->prev = NULL;
history_show_func.c:void			show_history_until(char *nb)
history_show_func.c:	t_history	*history;
history_show_func.c:	history = g_shell.history;
history_show_func.c:	while (history && j < len)
history_show_func.c:		ft_putendl(history->str);
history_show_func.c:		history = history->next;
history_show_func.c:void			show_history(void)
history_show_func.c:	t_history	*history;
history_show_func.c:	history = g_shell.history;
history_show_func.c:	while (history)
history_show_func.c:		ft_putendl(history->str);
history_show_func.c:		history = history->next;
history_show_func.c:void			show_history_rev(void)
history_show_func.c:	t_history	*history;
history_show_func.c:	i = g_shell.history_index;
history_show_func.c:	history = g_shell.history;
history_show_func.c:	while (history->next)
history_show_func.c:		history = history->next;
history_show_func.c:	while (history)
history_show_func.c:		ft_putendl(history->str);
history_show_func.c:		history = history->prev;
history_show_func.c:void			show_history_rev_until(char *nb)
history_show_func.c:	t_history	*history;
history_show_func.c:	i = g_shell.history_index;
history_show_func.c:	history = g_shell.history;
history_show_func.c:	while (history->next)
history_show_func.c:		history = history->next;
history_show_func.c:	while (history && i > j)
history_show_func.c:		ft_putendl(history->str);
history_show_func.c:		history = history->prev;
history_tools.c:/*   history_tools.c                                    :+:      :+:    :+:   */
history_tools.c:char			*get_history_i(int i)
history_tools.c:	t_history	*history;
history_tools.c:	history = g_shell.history;
history_tools.c:		history = history->next;
history_tools.c:	return (history->str);
history_tools.c:		ft_putendl("sh: history: illegal usage");
history_tools.c:		ft_putstr("sh: history: ");
history_tools.c:int				ft_get_lenght_list(t_history *history)
history_tools.c:	while (history)
history_tools.c:		history = history->next;
history_tools.c:void			show_helper_history(void)
history_tools.c:	ft_putendl("        history");
history_tools.c:	ft_putendl("        history [n]");
history_tools.c:	ft_putendl("        history [-crw]");
history_tools.c:	ft_putendl("        history -d offset");
history_tools.c:	ft_putendl("        history -s arg");
main.c:	built[4].str = "history";
main.c:	built[4].blt = history;
press_key3.c:	t_history	*history;
press_key3.c:	history = g_shell.history;
press_key3.c:	if (g_shell.history_index < get_history_length(history))
press_key3.c:			replace_shell_backslash_line(get_history_i(g_shell.history_index));
press_key3.c:			replace_shell_line(get_history_i(g_shell.history_index));
press_key3.c:		g_shell.history_index++;
press_key3.c:	else if (g_shell.history_index == get_history_length(history))
press_key3.c:		g_shell.history_index = get_history_length(history) + 1;
press_key5.c:		add_to_history(g_shell.history, g_shell.shell_line);
press_key5.c:		g_shell.history_index = get_history_length();
press_key7.c:	t_history	*history;
press_key7.c:	if (g_shell.history_index > 0)
press_key7.c:		history = g_shell.history;
press_key7.c:			g_shell.history_index--;
press_key7.c:			if (g_shell.history_index > 0)
press_key7.c:				get_history_i(g_shell.history_index - 1));
press_key7.c:			if (g_shell.history_index == 0)
press_key7.c:				g_shell.history_index++;
press_key7.c:		else if (g_shell.history_index != 1)
press_key7.c:			g_shell.history_index--;
press_key7.c:			replace_shell_line(get_history_i(g_shell.history_index - 1));
press_key7.c:void			print_history(t_history *history)
press_key7.c:	t_history	*his;
press_key7.c:	his = history;
redi_handler.c:	t_history	*hist;
redi_heredochandler.c:void		free_heredoc(t_history *hist)
redi_heredochandler.c:	t_history *t;
redi_heredochandler.c:void		heredoc_to_stdin(t_liste2 *l, t_history *hist, t_history *t)
shell.c:	g_shell.history_index = -1;
shell.c:	g_shell.history = (t_history *)malloc(sizeof(t_history));
shell.c:	g_shell.history->next = NULL;
shell.c:	g_shell.history->prev = NULL;
shell.c:	g_shell.history->str = NULL;
shell.c:t_history			*double_left(char *fin)
shell.c:	t_history		*hered;
shell.c:	hered = (t_history *)malloc(sizeof(t_history));
shell.c:	g_shell.history_index = get_history_length() + 1;
shell.c:		add_to_history(hered, g_shell.shell_line);
shell2.c:		g_shell.history_index = get_history_length() + 1;
shell2.c:	if (g_shell.history_index == get_history_length() + 1)
valgrind:==46753==    by 0x100001E11: add_to_history (history_option.c:30)
valgrind:==46753==    by 0x100001E11: add_to_history (history_option.c:30)
valgrind:==46753==    by 0x100001E11: add_to_history (history_option.c:30)
