/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 00:23:07 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/19 01:31:22 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env_b(t_list *env_var, t_commands *args)
{
	redirect_out(args->out);
	if (!env_var)
		return (0);
	ft_lstprint_str(env_var, args->out);
	return (0);
}
