/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:51:41 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/19 01:30:11 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    exit_b(t_commands *command, t_list **env_var, t_commands **args)
{
    unsigned long long  status;

    redirect_out(command->out);
    status = ft_atoul(command->command[1]);
    if (status > 9223372036854775807)
        status = 255;
    ft_clear_commands(args);
	ft_lstclear(env_var, free);
    exit(status);
}
