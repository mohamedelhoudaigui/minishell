/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 01:22:37 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/19 02:37:51 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	unset(t_list **env_vars, t_commands *args)
{
	t_list	*node;
	int		i;
	char	*var;
	
	if (!env_vars || *env_vars == NULL)
		return (0);
	redirect_out(args->out);
	i = 1;
	while (args->command[i])
	{
		var = args->command[i];
		node = ft_lstfind_str(env_vars, var);
		if (node)
			remove_env_var(env_vars, &node);
		i++;
	}
	return (0);
}