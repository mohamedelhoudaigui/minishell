/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:27:24 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/06 22:32:32 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"

int	check_command_bb(char *command)
{
	if (ft_strncmp(command, "echo", ft_strlen(command) + 5) == 0)
		return (0);
	else if (ft_strncmp(command, "pwd", ft_strlen(command) + 3) == 0)
		return (0);
	else if (ft_strncmp(command, "cd", ft_strlen(command) + 2) == 0)
		return (0);
	else if (ft_strncmp(command, "exit", ft_strlen(command) + 4) == 0)
		return (0);
	else if (ft_strncmp(command, "env", ft_strlen(command) + 3) == 0)
		return (0);
	else if (ft_strncmp(command, "unset", ft_strlen(command) + 5) == 0)
		return (0);
	else if (ft_strncmp(command, "export", ft_strlen(command) + 6) == 0)
		return (0);
	return (1);
}

int	fork_or_not(t_commands *args)
{
	if (args && args->next == NULL && args->command[0] != NULL
		&& args->command[0][0] != '\0')
	{
		return (check_command_bb(args->command[0]));
	}
	return (1);
}

void	wait_and_exit_status(int *child, int n_commands)
{
	int	status;
	int	i;

	i = 0;
	while (i < n_commands)
	{
		waitpid(child[i], &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		i++;
	}
}

void	redirect_in_out_command(t_commands *args, t_list **env_adr)
{
	redirect_in(args->in);
	redirect_out(args->out);
	if (args->in != -1 && args->out != -1)
		redirect_command(env_adr, args);
	else
		g_exit_status = 1;
}

void	close_pipes(int **pipes)
{
	int	*fd;
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (pipes[i])
	{
		fd = (int *)pipes[i];
		close(fd[0]);
		close(fd[1]);
		i++;
	}
}
