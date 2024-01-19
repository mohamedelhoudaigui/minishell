/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 03:28:00 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/19 04:49:52 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_export(t_list *env_var)
{
	while (env_var)
	{
		printf("declare -x ");
		printf("%s\n", env_var->content);
		env_var = env_var->next;
	}
}

int	calculate_to_eq(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=')
		i++;
	return (i);
}

int	export(t_list **env_var, t_commands *args)
{
	int		i;
	t_list	*node;
	char	*var_name;

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
		if (ft_strchr(args->command[i], '=') != NULL)
		{
			var_name = ft_substr(args->command[i], 0, calculate_to_eq(args->command[i]));
			node = ft_lstfind_str(env_var,var_name);
			free(var_name);
			if (node == NULL)
				add_env_var(env_var, args->command[i]);
			else
			{
				free(node->content);
				node->content = ft_strdup(args->command[i]);
			}
		}
		i++;
	}
	return (0);
}