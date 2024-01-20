/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 03:28:13 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/20 06:45:02 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_commands	*create_args(int ac, char **av)
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
	command = ft_new_command(0, 1);
	command->command = args;
	
	if (!command)
		return (NULL);
	return (command);
}

int	redirect_command(t_list **env, t_commands *args)
{
	char	*com_name;
	int		return_value;

	return_value = 0;
	com_name = args->command[0];
	if (ft_strncmp(com_name, "echo", ft_strlen(com_name)) == 0)
		return_value = echo(args);
	else if (ft_strncmp(com_name, "pwd", ft_strlen(com_name)) == 0)
		return_value = pwd(args);
	else if (ft_strncmp(com_name, "cd", ft_strlen(com_name)) == 0)
		return_value = cd(env, args);
	else if (ft_strncmp(com_name, "exit", ft_strlen(com_name)) == 0)
		exit_b(args, env);
	else if (ft_strncmp(com_name, "env", ft_strlen(com_name)) == 0)
		return_value = env_b(*env, args);
	else if (ft_strncmp(com_name, "unset", ft_strlen(com_name)) == 0)
		return_value = unset(env, args);
	else if (ft_strncmp(com_name, "export", ft_strlen(com_name)) == 0)
		return_value = export(env, args);
	return (return_value);
}

int	execution(int ac, char **av, t_list **env_adr)
{
	t_commands *args;
	int			i;
	int			return_value;

	(void)env_adr;
	i = 0;
	args = create_args(ac, av);
	if (!args)
		return (1);
	
	return_value = redirect_command(env_adr, args);
	// ft_lstprint_str(*env_adr, 1);
	ft_clear_commands(&args);
	ft_lstclear(env_adr, free);
	return (0);
}