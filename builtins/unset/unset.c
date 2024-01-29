/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 01:22:37 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/29 02:49:00 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parse_varname_unset(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	if (ft_isalpha(arg[0]) == 0)
		return (1);
	while (arg[i])
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
			return (1);
		i++;
	}
	return (0);
}


int	unset(t_list **env_vars, t_commands *args)
{
	t_list	*node;
	int		i;
	char	*var;
	char	*var_eq;
	
	if (!env_vars || *env_vars == NULL || !args->command[1])
	{
		exit_status = 0;
		return (0);
	}
	i = 1;
	while (args->command[i])
	{
		var = args->command[i];
		if (parse_varname_unset(var) == 1)
		{
			ft_putstr_fd("unset : %s : not a valid identifier\n", 2);
			exit_status = 1;
		}
		else
		{
			var_eq = ft_strjoin(var, "=");
			node = ft_lstfind_str(env_vars, var_eq);
			if (node)
				remove_env_var(env_vars, &node);
			free(var_eq);
			exit_status = 0;
		}
		i++;
	}
	return (0);
}