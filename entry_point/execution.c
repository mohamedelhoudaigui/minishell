/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 03:28:13 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/22 06:12:18 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_command(t_list **env, t_commands *args)
{
	char	*com_name;
	int		return_value;

	return_value = 0;
	com_name = args->command[0];
	if (ft_strncmp(com_name, "echo", ft_strlen(com_name)) == 0)
		return_value = echo(args);
	else if (ft_strncmp(com_name, "pwd", ft_strlen(com_name)) == 0)
		return_value = pwd();
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
	else
		return_value = execute_command(*env, args);
	return (return_value);
}

int	fork_or_not(t_commands *args)
{
	if (args->next == NULL)
	{
		if (ft_strncmp(args->command[0], "echo", ft_strlen(args->command[0])) == 0)
			return (0);
		else if (ft_strncmp(args->command[0], "pwd", ft_strlen(args->command[0])) == 0)
			return (0);
		else if (ft_strncmp(args->command[0], "cd", ft_strlen(args->command[0])) == 0)
			return (0);
		else if (ft_strncmp(args->command[0], "exit", ft_strlen(args->command[0])) == 0)
			return (0);
		else if (ft_strncmp(args->command[0], "env", ft_strlen(args->command[0])) == 0)
			return (0);
		else if (ft_strncmp(args->command[0], "unset", ft_strlen(args->command[0])) == 0)
			return (0);
		else if (ft_strncmp(args->command[0], "export", ft_strlen(args->command[0])) == 0)
			return (0);
	}
	return (1);
}


int	process_job(t_list **env_adr, t_commands *args, int *child, int i)
{
	child[i] = fork();
	if (child[i] == -1)
		return (-1);
	if (child[i] == 0)
	{
		redirect_in(args->in);
		redirect_out(args->out);
		redirect_command(env_adr, args);
	}
	return (0);
}

int	execution(t_list **env_adr, t_commands *args)
{
	int			return_value;
	int			fork_num;
	int			*child;
	int			n_commands;
	int			i;

	if (!env_adr || *env_adr == NULL || !args)
		return (-1);
	return_value = 0;
	fork_num = fork_or_not(args);
	n_commands = ft_command_size(args);
	child = (int *)ft_calloc(n_commands, sizeof(int));
	i = 0;
	if (fork_num == 1)
	{
		while (args)
		{
			process_job(env_adr, args, child, i);
			i++;
			args = args->next;
		}
		i = 0;
		while (i < n_commands)
			waitpid(child[i++], &return_value, 0);
	}
	else
	{
		redirect_in(args->in);
		redirect_out(args->out);
		return_value = redirect_command(env_adr, args);
	}
	free(child);
	return (return_value);
}