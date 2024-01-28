/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 03:28:00 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/28 00:45:43 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	export(t_list **env_var, t_commands *args)
{
	int		i;
	int		flag;
	char	*arg;
	char	*key;
	char	*value;

	if (!env_var)
	{
		exit_status = 1;
		return (1);
	}
	if (args->command[1] == NULL)
	{
		print_export(*env_var);
		exit_status = 0;
		return (0);
	}
	i = 1;
	while (args->command[i])
	{
		arg = args->command[i];
		flag = handle_flag(arg);
		if (parse_varname(arg) == 1)
		{
			ft_putstr_fd("export : not a valid identifier\n", 2);
			exit_status = 1;
		}
		else
			exit_status = 0;
		if (flag != 2 && parse_varname(arg) == 0)
		{
			key = get_key(arg);
			value = get_value(arg);
			if (flag == 1)
				update_env_var(env_var, key, value);
			else if (flag == 0)
				join_env_var(env_var, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	return (0);
}