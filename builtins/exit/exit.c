/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:51:41 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/27 21:01:08 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//need some modification ! protect max long long, throw error and return 255 ! 

void    exit_b(t_commands *command, t_list **env_var)
{
    long long		status;
    unsigned char	status_char;

    if (command->command[1] == NULL)
    {
        printf("exit\n");
        ft_clear_commands(&command);
	    ft_lstclear(env_var, free);
        exit(exit_status);
    }
    status = ft_atoul(command->command[1]);
    status_char = (unsigned char)status;
    printf("exit\n");
    ft_clear_commands(&command);
	ft_lstclear(env_var, free);
    exit(status_char);
}
