/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 02:25:44 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/19 05:17:49 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*create_args(void)
{
	t_commands *command;
	char	**args;

	args = (char **)malloc(sizeof(char *) * 3);
	if (!args)
		return (NULL);
	args[0] = ft_strdup("export");
	args[1] = ft_strdup("USER=hello");
	args[2] = NULL;
	command = ft_new_command(args, 0, 1);
	if (!command)
		return (NULL);
	return (command);
}


int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_list	*env_var;
	t_commands	*args;
	
	args = create_args();
	env_var = get_env_var(env);
	if (!args)
		return (1);
	ft_lstprint_str(env_var, args->out);
	export(&env_var, args);
	ft_lstprint_str(env_var, args->out);
	ft_clear_commands(&args);
	ft_lstclear(&env_var, free);
	return (0);
}

// shell level not implemented !
// cd for deleted folders
// += in export