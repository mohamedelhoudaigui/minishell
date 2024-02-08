/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 03:51:34 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/08 12:49:44 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"

char	*expande_exit_status(void)
{
	char	*result;

	result = ft_itoa(g_exit_status);
	if (!result)
		return (NULL);
	return (result);
}

char	*expande_var(t_list **env_var, char *var)
{
	char	*result;
	t_list	*node;
	int		i;
	char	*node_content;

	if (!var)
		return (NULL);
	if (var[1] == '?' && var[2] == '=' && var[3] == '\0')
		return (expande_exit_status());
	var++;
	node = ft_lstfind_str(env_var, var);
	if (!node || !node->content)
		return (NULL);
	node_content = (char *)node->content;
	i = -1;
	while (node_content[++i])
	{
		if (node_content[i - 1] == '=')
			break ;
	}
	result = ft_strdup(&node_content[i]);
	if (!result)
		return (NULL);
	return (result);
}
