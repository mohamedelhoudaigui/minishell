/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 01:36:46 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/25 02:10:55 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	close_unused_pipes(int i, int **pipes, int n_commands)
{
	int	j;

	if (i == 0)
	{
		j = 1;
		while (pipes[j])
		{
			close(pipes[j][0]);
			close(pipes[j][1]);
			j++;
		}
	}
	else if (i == n_commands - 1)
	{
		j = 0;
		while (pipes[j])
		{
			if (j != i - 1)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
			}
			j++;
		}
	}
	else
	{
		j = 0;
		while (pipes[j])
		{
			if (j != i && j != i - 1)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
			}
			j++;
		}
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