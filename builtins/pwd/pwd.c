/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:53:18 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/27 20:49:48 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd(t_commands *args)
{
	char	buffer[5000];

	if (args && args->command && args->command[1])
	{
		ft_putstr_fd("pwd : invalid argument\n", 2);
		exit_status = 1;
		return (1);
	}
	if (getcwd(buffer, sizeof(buffer)) != NULL)
		printf("%s\n", buffer);
	else
	{
		perror("pwd");
		return (1);
	}
	return (exit_status);
}