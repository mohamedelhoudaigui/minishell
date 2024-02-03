/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 02:25:44 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/03 23:09:56 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exit_status;

t_commands	*create_args(int ac, char **av, int in, int out)
{
	t_commands *command;
	char	**args;
	int		i;

	i = 0;
	args = (char **)ft_calloc(sizeof(char *), ac);
	if (!args)
		return (NULL);
	while (i < ac - 1)
	{
		args[i] = ft_strdup(av[i + 1]);
		i++;
	}
	command = ft_new_command(in, out);
	if (!command)
		return (NULL);
	command->command = args;
	return (command);
}

void	f()
{
	printf("\n\n");
	int num = getpid();
	char	*gg = ft_itoa(num);
	char	*bb = ft_strjoin("lsof -p ", gg);
	free(gg);
	system(bb);
	free(bb);
	printf("\n\n");
	system("leaks minishell");
}

t_redir	*create_redir(char *str, int type, bool flage)
{
	t_redir	*res;
	char	*file_name;

	res = (t_redir *)ft_calloc(sizeof(t_redir), 1);
	file_name = ft_strdup(str);
	res->file = file_name;
	res->next = NULL;
	res->type = type;
	res->flage = flage;
	return (res);
}

t_parsing	*create_com(char **av)
{
	t_parsing	*args;
	t_redir		*in;
	t_redir		*out;

	in = create_redir("ll", 3, true);
	out = NULL;
	
	args = (t_parsing *)ft_calloc(1, sizeof(t_parsing));
	args->command = (char **)ft_calloc(sizeof(char *), 2);
	args->command[0] = ft_strdup(av[1]);
	args->in_fd =  in;
	args->out_fd = out;
	args->next = NULL;
	return (args);
}

void	reset_fd(int o_stdin, int o_stdout)
{
	dup2(o_stdin, 0);
	dup2(o_stdout, 1);
	close(o_stdin);
	close(o_stdout);
}

int	main(int ac, char **av, char **env)
{
	t_list		*env_var;
	t_commands	*commands;
	t_parsing	*args;
	int			o_stdin;
	int			o_stdout;

	if (ac < 2)
		return (0);
	// atexit(f);
	o_stdin = dup(0);
    o_stdout = dup(1);

	args = create_com(av);
	// args2 = create_com(av);
	// free(args2->command[0]);
	// args2->command[0] = ft_strdup("wc");
	// args2->out_fd = NULL;
	// args2->out_fd->file = ft_strdup("bb");
	// args2->out_fd->type = 2;
	// args2->out_fd = NULL;
	// args2->in_fd = NULL;
	// args->next = args2;
	env_var = get_env_var(env);
	commands = open_fd(args, &env_var);
	execution(&env_var, commands);
	ft_lstclear(&env_var, free);
	free_parse_args(args);
	ft_clear_commands(&commands);
	close_all_fd(commands);
	reset_fd(o_stdin, o_stdout);
	return (exit_status);
}
