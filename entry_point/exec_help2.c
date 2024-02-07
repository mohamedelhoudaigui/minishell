/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_help2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:39:13 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/06 23:49:41 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"

void	help(t_commands *args)
{
	close_all_fd(args);
	g_exit_status = 1;
	exit(g_exit_status);
}

int	process_job(t_proc_job *pr)
{
	int	i;

	i = pr->i;
	pr->child[i] = fork();
	if (pr->child[i] == -1)
		return (-1);
	if (pr->child[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (pr->pipes != NULL)
			redirect_pipes(i, pr->pipes, pr->n_commands);
		redirect_in(pr->args->in);
		redirect_out(pr->args->out);
		if (pr->args->in != -1 && pr->args->out != -1)
			redirect_command(pr->env_adr, pr->args);
		else
			help(pr->args);
		close_all_fd(pr->args);
		exit(g_exit_status);
	}
	return (0);
}
