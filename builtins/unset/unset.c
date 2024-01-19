/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 01:22:37 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/19 03:33:45 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	unset(t_list **env_vars, t_commands *args)
{
	t_list	*node;
	int		i;
	char	*var;
	char	*var_eq;
	
	redirect_out(args->out);
	redirect_in(args->in);
	if (!env_vars || *env_vars == NULL || !args->command[1])
		return (0);
	i = 1;
	while (args->command[i])
	{
		var = args->command[i];
		var_eq = ft_strjoin(var, "=");
		node = ft_lstfind_str(env_vars, var_eq);
		if (node)
			remove_env_var(env_vars, &node);
		free(var_eq);
		i++;
	}
	return (0);
}