/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 01:13:28 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/06 01:26:51 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"

void	cmd_sig_handel(int signo)
{
	if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		exit_status = 131;
		exit(exit_status);
	}
	else if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		exit_status = 130;
		exit(exit_status);
	}
}

void	cmd_sig_loop(int signo)
{
	if (signo == SIGINT)
	{
		exit_status = 130;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}