/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 01:13:28 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/06 23:54:27 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"

void	sig_int(int signo)
{
	(void) signo;
	g_exit_status = 1;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	cmd_sig_loop(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int);
}

void	here_doc_int(int signo)
{
	(void)signo;
	g_exit_status = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	ioctl(0, TIOCSTI, "\4");
}

void	here_doc_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, here_doc_int);
}
