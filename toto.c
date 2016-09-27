9c9
< /*   Updated: 2016/09/27 15:08:51 by cmichaud         ###   ########.fr       */
---
> /*   Updated: 2016/09/24 17:36:19 by cmichaud         ###   ########.fr       */
53,74d52
< int			sub_exec_norm(t_data *data)
< {
< 	if (!ft_strcmp(data->args[0], "exit"))
< 		exit_on_pipe(data, data->args);
< 	else if (!ft_strcmp(data->args[0], "export"))
< 		export_on_pipe(data);
< 	else if (!ft_strcmp(data->args[0], "cd"))
< 		cd_on_pipe(data);
< 	else if (ft_strcmp(data->args[0], "env") == 0)
< 		env_on_pipe(data);
< 	else if (ft_strcmp(data->args[0], "unset") == 0)
< 		exit(0);
< 	else if (ft_strcmp(data->args[0], "echo") == 0)
< 	{
< 		callecho(data->args);
< 		exit((data->binreturn = 0));
< 	}
< 	else
< 		return (0);
< 	return (1);
< }
< 
83c61
< 				(ft_strcmp(data->args[0], "$?") == 0))
---
> 				 (ft_strcmp(data->args[0], "$?") == 0))
91a70,84
> 	else if (!ft_strcmp(data->args[0], "exit"))
> 		exit_on_pipe(data, data->args);
> 	else if (!ft_strcmp(data->args[0], "export"))
> 		export_on_pipe(data);
> 	else if (!ft_strcmp(data->args[0], "cd"))
> 		cd_on_pipe(data);
> 	else if (ft_strcmp(data->args[0], "env") == 0)
> 		env_on_pipe(data);
> 	else if (ft_strcmp(data->args[0], "unset") == 0)
> 		exit(0);
> 	else if (ft_strcmp(data->args[0], "echo") == 0)
> 	{
> 		callecho(data->args);
> 		exit((data->binreturn = 0));
> 	}
94c87
< 	else if (!sub_exec_norm(data) && !is_a_builtin(data->args[0]))
---
> 	else if (!is_a_builtin(data->args[0]))
105c98
< //			ft_reset_term(g_shell.term_reset.term_copy);
---
> 			ft_reset_term();
