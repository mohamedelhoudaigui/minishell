/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 03:28:00 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/20 03:16:16 by mel-houd         ###   ########.fr       */
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

	redirect_out(args->out);
	redirect_in(args->in);
	if (!env_var)
		return (1);
	if (args->command[1] == NULL)
	{
		print_export(*env_var);
		return (0);
	}
	i = 1;
	while (args->command[i])
	{
		arg = args->command[i];
		flag = handle_flag(arg);
		if (flag != 2)
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