/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 02:25:44 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/03 08:41:18 by mel-houd         ###   ########.fr       */
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
	system("leaks minishell");
}

t_parsing	*create_com(char **av)
{
	t_parsing	*args;
	t_redir		*in;
	t_redir		*out;

	// out = (t_redir *)ft_calloc(1, sizeof(t_redir));
	// out->file = ft_strdup("/ss");
	// out->type = 1;
	// out->next = NULL;
	out = NULL;
	in = (t_redir *)ft_calloc(1, sizeof(t_redir));
	in->file = ft_strdup("/exam");
	in->type = 1;
	in->next = NULL;
	// in = NULL;
	args = (t_parsing *)ft_calloc(1, sizeof(t_parsing));
	args->command = (char **)ft_calloc(sizeof(char *), 2);
	args->command[0] = ft_strdup(av[1]);
	args->in_fd =  in;
	args->out_fd = out;
	args->next = NULL;
	return (args);
}

int	main(int ac, char **av, char **env)
{
	t_list		*env_var;
	t_commands	*commands;
	t_parsing	*args;
	// t_parsing	*args2;

	if (ac < 2)
		return (0);
	atexit(f);
	int o_stdin = dup(0);
    int o_stdout = dup(1);

	args = create_com(av);
	// args2 = create_com(av);
	// free(args2->command[0]);
	// args2->command[0] = ft_strdup("wc");
	// args2->in_fd = (t_redir *)ft_calloc(1, sizeof(t_redir));
	// args2->in_fd = NULL;
	// args2->out_fd = NULL;
	// args->next = args2;
	env_var = get_env_var(env);
	commands = open_fd(args, &env_var);
	execution(&env_var, commands);
	ft_lstclear(&env_var, free);
	close_all_fd(commands);
	ft_clear_commands(&commands);
	free_parse_args(args);
	dup2(o_stdin, 0);
	dup2(o_stdout, 1);
	return (exit_status);
}
