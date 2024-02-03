/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 02:25:44 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/03 06:10:07 by mel-houd         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	t_list		*env_var;
	t_commands	*commands;
	t_parsing	*args;
	t_redir		*in;
	t_redir		*out;

	// atexit(f);
	out = NULL;
	in = (t_redir *)ft_calloc(1, sizeof(t_redir));
	in->file = ft_strdup("test.txt");
	in->type = 1;
	in->next = NULL;
	args = (t_parsing *)ft_calloc(1, sizeof(t_parsing));
	args->command = (char **)ft_calloc(sizeof(char *), 3);
	args->command[0] = ft_strdup(av[1]);
	args->command[1] = ft_strdup(av[2]);
	args->in_fd =  in;
	args->out_fd = out;
	args->next = NULL;
	commands = open_fd(args);
	env_var = get_env_var(env);
	execution(&env_var, commands);
	// args->next = args2;
	// args2->next = args3;
	// args3->next = args4;
	// args4->next = args5;
	
	// execution(&env_var, args);
	free(args->command[0]);
	free(args->command[1]);
	free(args->command);
	free(args);
	free(in->file);
	free(in);
	ft_lstclear(&env_var, free);
	ft_clear_commands(&commands);
	return (exit_status);
}
