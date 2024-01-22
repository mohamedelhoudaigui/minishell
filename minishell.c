/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 02:25:44 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/22 04:56:51 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int			return_value;
	t_commands *args_2;

	// atexit(f);
	if (ac < 2)
		return (0);

	env_var = get_env_var(env);
	args = create_args(ac, av, 0, 1);
	args_2 = create_args(ac, av, 1, 1);
	if (!args || !env_var)
		return (1);
	free(args_2->command[0]);
	args_2->command[0] = ft_strdup("wc");
	args->next = args_2;
	return_value = execution(&env_var, args);
	ft_lstclear(&env_var, free);
	ft_clear_commands(&args);
	return (return_value);
}
