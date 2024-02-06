/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 01:13:28 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/06 17:40:26 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"

void	sig_int(int signo)
{
	(void) signo;
	g_exit_status = 1;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("\nlbroshell$ ", 1);
}

void	cmd_sig_loop(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int);
}

void	sig_command(int signo)
{
	if (signo == SIGINT)
	{
		g_exit_status = 130;
		exit(130);
	}
	if (signo == SIGQUIT)
	{
		g_exit_status = 131;
		exit(131);
	}
}
