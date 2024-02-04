/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 03:15:55 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/05 00:03:27 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	calculate_to(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=' && var[i] != '+')
		i++;
	return (i);
}

int	handle_flag(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
		i++;
	if (arg[i] == '+' && arg[i + 1] == '=')
		return (0);
	else if (arg[i] == '=')
		return (1);
	return (2);
}

char	*get_key(char *arg)
{
	int		i;
	char	*key;
	char	*key_eq;

	i = calculate_to(arg);
	key = ft_substr(arg, 0, i);
	if (!key)
		return (NULL);
	key_eq = ft_strjoin(key, "=");
	if (!key_eq)
		return (NULL);
	free(key);
	return (key_eq);
}

char	*get_value(char *arg)
{
	int		i;
	char	*value;

	i = calculate_to(arg);
	if (arg[i] == '+')
		i++;
	if (arg[i] == '=')
		i++;
	value = ft_substr(arg, i, ft_strlen(arg));
	if (!value)
		return (NULL);
	return (value);
}

int	parse_varname(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	if (ft_isalpha(arg[0]) == 0 && arg[0] != '_')
		return (1);
	while (arg[i])
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '=' && arg[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
