/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 13:36:48 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/21 13:38:07 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_command_size(t_commands *args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args)
	{
		i++;
		args = args->next;
	}
	return (i);
}
