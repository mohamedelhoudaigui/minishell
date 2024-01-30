/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 02:25:44 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/30 13:31:02 by mel-houd         ###   ########.fr       */
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
	t_commands	*args;
	t_commands	*args2;
	char		*expande_value;
	int			file;

	atexit(f);
	if (ac < 2)
		return (0);
	env_var = get_env_var(env);
	file = here_doc("ll", &env_var, true);
	args = create_args(ac, av, file, 1);
	execution(&env_var, args);
	ft_lstclear(&env_var, free);
	ft_clear_commands(&args);
	return (exit_status);
}
