/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 01:36:46 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/06 17:33:35 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"

void	close_pipes_from(int start, int **pipes, int exclude1, int exclude2)
{
	int	j;

	j = start;
	while (pipes[j])
	{
		if (j != exclude1 && j != exclude2)
		{
			close(pipes[j][0]);
			close(pipes[j][1]);
		}
		j++;
	}
}

void	close_unused_pipes(int i, int **pipes, int n_commands)
{
	if (i == 0)
	{
		close_pipes_from(1, pipes, -1, -1);
	}
	else if (i == n_commands - 1)
	{
		close_pipes_from(0, pipes, i - 1, -1);
	}
	else
	{
		close_pipes_from(0, pipes, i, i - 1);
	}
}

void	redirect_pipes(int i, int **pipes, int n_commands)
{
	if (i == 0)
	{
		close_unused_pipes(i, pipes, n_commands);
		close(pipes[0][0]);
		dup2(pipes[0][1], 1);
		close(pipes[0][1]);
	}
	else if (i == n_commands - 1)
	{
		close_unused_pipes(i, pipes, n_commands);
		close(pipes[i - 1][1]);
		dup2(pipes[i - 1][0], 0);
		close(pipes[i - 1][0]);
	}
	else
	{
		close_unused_pipes(i, pipes, n_commands);
		close(pipes[i][0]);
		close(pipes[i - 1][1]);
		dup2(pipes[i][1], 1);
		dup2(pipes[i - 1][0], 0);
		close(pipes[i][1]);
		close(pipes[i - 1][0]);
	}
}
