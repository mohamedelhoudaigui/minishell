/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 01:22:37 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/08 20:41:00 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	parse_varname_unset(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	if (ft_isalpha(arg[0]) == 0 && arg[0] != '_')
		return (1);
	while (arg[i])
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	handle_env_vars(t_list **env_vars, t_commands *args)
{
	if (!env_vars || *env_vars == NULL || !args->command[1])
	{
		g_exit_status = 0;
		return (0);
	}
	return (1);
}

void	handle_command_unset(t_list **env_vars, char *var)
{
	t_list	*node;
	char	*var_eq;

	var_eq = ft_strjoin(var, "=");
	node = ft_lstfind_str(env_vars, var_eq);
	if (node)
		remove_env_var(env_vars, &node);
	free(var_eq);
	g_exit_status = 0;
}

int	unset(t_list **env_vars, t_commands *args)
{
	int		i;
	char	*var;

	if (!handle_env_vars(env_vars, args))
		return (0);
	i = 1;
	while (args->command[i])
	{
		var = args->command[i];
		if (parse_varname_unset(var) == 1)
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(var, 2);
			ft_putstr_fd(" : not a valid identifier\n", 2);
			g_exit_status = 1;
		}
		else
			handle_command_unset(env_vars, var);
		i++;
	}
	return (0);
}
