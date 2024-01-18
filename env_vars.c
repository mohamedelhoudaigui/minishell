/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:40:59 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/17 12:24:45 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_env_var(char **env)
{
	int		i;
	t_list	*head;
	t_list	*node;

	if (!env || env[0] == NULL)
	{
		perror("no env vars\n");
		return (NULL);
	}
	i = 0;
	head = ft_lstnew(ft_strdup(env[i]));
	if (env[1] == NULL)
		return (head);
	while (env[++i])
	{
		node = ft_lstnew(ft_strdup(env[i]));
		if (!node)
			return (NULL);
		ft_lstadd_back(&head, node);
	}
	return (head);
}