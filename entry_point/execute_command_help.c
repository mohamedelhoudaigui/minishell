/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_help.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:34:18 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/06 17:34:35 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"

char	**morph_env(t_list *env_var)
{
	char	**env;
	int		size;
	int		i;

	if (!env_var || env_var->content == NULL)
		return (NULL);
	size = ft_lstsize(env_var);
	env = (char **)ft_calloc(sizeof(char *), size + 1);
	if (!env)
		return (NULL);
	i = 0;
	while (i < size)
	{
		env[i] = ft_strdup(env_var->content);
		i++;
		env_var = env_var->next;
	}
	return (env);
}

char	**morph_args(t_commands *args)
{
	char	**old_args;
	int		i;
	char	**args_str;
	int		size;

	if (!args || args->command == NULL)
		return (NULL);
	old_args = args->command;
	size = ft_ptrsize((void **)old_args);
	if (size == -1)
		return (NULL);
	args_str = (char **)ft_calloc(sizeof(char *), size + 1);
	if (!args_str)
		return (NULL);
	i = 0;
	while (old_args[i])
	{
		args_str[i] = ft_strdup(old_args[i]);
		i++;
	}
	return (args_str);
}
