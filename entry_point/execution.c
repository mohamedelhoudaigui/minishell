/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 03:28:13 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/08 18:14:03 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"

void	free_pipes(int **pipes)
{
	int	i;

	i = 0;
	if (pipes != NULL)
	{
		while (pipes[i])
			free(pipes[i++]);
		free(pipes);
	}
}

int	redirect_command(t_list **env, t_commands *args)
{
	char	*com_name;

	com_name = args->command[0];
	if (com_name[0] == '\0')
	{
		execute_command(*env, args);
		return (0);
	}
	if (ft_strncmp(com_name, "echo", ft_strlen(com_name) + 4) == 0)
		echo(args);
	else if (ft_strncmp(com_name, "pwd", ft_strlen(com_name) + 3) == 0)
		pwd(args, env);
	else if (ft_strncmp(com_name, "cd", ft_strlen(com_name) + 2) == 0)
		cd(env, args);
	else if (ft_strncmp(com_name, "exit", ft_strlen(com_name) + 4) == 0)
		exit_b(args, env);
	else if (ft_strncmp(com_name, "env", ft_strlen(com_name) + 3) == 0)
		env_b(*env, args);
	else if (ft_strncmp(com_name, "unset", ft_strlen(com_name) + 5) == 0)
		unset(env, args);
	else if (ft_strncmp(com_name, "export", ft_strlen(com_name) + 6) == 0)
		export(env, args);
	else
		execute_command(*env, args);
	return (0);
}

int	**create_pipes(int n_pipes)
{
	int		i;
	int		**pipes;

	if (n_pipes == 0)
		return (NULL);
	pipes = (int **)ft_calloc(sizeof(int *), n_pipes + 1);
	i = 0;
	while (i < n_pipes)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}

void	handle_fork_execution(t_list **env_adr, t_commands *args,
		int *child, int n_commands)
{
	int			**pipes;
	int			i;
	t_proc_job	*proc_job;

	i = 0;
	pipes = create_pipes(n_commands - 1);
	proc_job = (t_proc_job *)malloc(sizeof(t_proc_job));
	while (args)
	{
		proc_job->i = i;
		proc_job->env_adr = env_adr;
		proc_job->args = args;
		proc_job->child = child;
		proc_job->pipes = pipes;
		proc_job->n_commands = n_commands;
		process_job(proc_job);
		i++;
		args = args->next;
	}
	close_pipes(pipes);
	wait_and_exit_status(child, n_commands);
	free_pipes(pipes);
	free(proc_job);
}

int	execution(t_list **env_adr, t_commands *args)
{
	int	fork_num;
	int	*child;
	int	n_commands;

	if (!args)
		return (0);
	fork_num = fork_or_not(args);
	n_commands = ft_command_size(args);
	child = (int *)ft_calloc(n_commands, sizeof(int));
	if (fork_num == 1)
		handle_fork_execution(env_adr, args, child, n_commands);
	else
		redirect_in_out_command(args, env_adr);
	free(child);
	return (0);
}
