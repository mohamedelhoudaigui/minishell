/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:51:41 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/06 17:40:26 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	check_alphanum(char *number)
{
	int	i;

	i = 0;
	while (number[i])
	{
		if (!ft_isdigit(number[i]))
			return (0);
		i++;
	}
	return (1);
}

void	normal_exit(t_commands *command, t_list **env_var)
{
	printf("exit\n");
	ft_clear_commands(&command);
	ft_lstclear(env_var, free);
	exit(g_exit_status);
}

void	exit_b(t_commands *command, t_list **env_var)
{
	long long		status;
	unsigned char	status_char;

	if (command->command[1] == NULL)
		normal_exit(command, env_var);
	if (command->command[2] != NULL)
	{
		g_exit_status = 1;
		ft_putstr_fd("exit : too many arguments\n", 2);
		return ;
	}
	status = ft_atoul(command->command[1]);
	status_char = (unsigned char)status;
	printf("exit\n");
	if (check_alphanum(command->command[1]) == 0)
	{
		ft_putstr_fd("exit : numeric argument required\n", 2);
		g_exit_status = 255;
		ft_clear_commands(&command);
		ft_lstclear(env_var, free);
		exit(g_exit_status);
	}
	ft_clear_commands(&command);
	ft_lstclear(env_var, free);
	exit(status_char);
}
