/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_help2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:04:03 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/06 17:04:52 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

void	swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	bubble_sort_string(char **env, int size)
{
	int	swapped;
	int	i;

	i = 0;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (env[i] && i < size - 1)
		{
			if (ft_strncmp(env[i], env[i + 1], ft_strlen(env[i])) > 0)
			{
				swap_strings(&env[i], &env[i + 1]);
				swapped = 1;
			}
			i++;
		}
	}
}

void	print_export(t_list *env_var)
{
	char	**env;
	int		i;

	if (!env_var || env_var->content == NULL)
		return ;
	env = morph_env(env_var);
	i = 0;
	while (env[i])
		i++;
	bubble_sort_string(env, i);
	i = 0;
	while (env[i])
	{
		printf("declare -x ");
		printf("%s\n", env[i]);
		i++;
	}
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}
