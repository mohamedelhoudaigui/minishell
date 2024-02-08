/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 03:28:00 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/08 12:58:17 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	handle_env_var(t_list **env_var)
{
	if (!env_var)
	{
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

int	handle_args(t_list **env_var, t_commands *args)
{
	if (args->command[1] == NULL)
	{
		print_export(*env_var);
		g_exit_status = 0;
		return (0);
	}
	return (1);
}

void	handle_command(t_list **env_var, char *arg, int flag)
{
	char	*key;
	char	*value;

	if (parse_varname(arg) == 0)
	{
		key = get_key(arg);
		value = get_value(arg);
		if (flag == 1 || flag == 2)
			update_env_var(env_var, key, value);
		else if (flag == 0)
			join_env_var(env_var, key, value);
		free(key);
		free(value);
	}
}

int	export(t_list **env_var, t_commands *args)
{
	int		i;
	int		flag;
	char	*arg;

	if (handle_env_var(env_var))
		return (1);
	if (!handle_args(env_var, args))
		return (0);
	i = 1;
	while (args->command[i])
	{
		arg = args->command[i];
		flag = handle_flag(arg);
		if (parse_varname(arg) == 1)
		{
			ft_putstr_fd("export : not a valid identifier\n", 2);
			g_exit_status = 1;
		}
		else
			g_exit_status = 0;
		handle_command(env_var, arg, flag);
		i++;
	}
	return (0);
}
