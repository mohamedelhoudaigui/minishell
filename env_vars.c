/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:40:59 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/19 02:36:17 by mel-houd         ###   ########.fr       */
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

void	create_env_var(t_list **head, char *env_var_name, char *arg)
{
	t_list	*new_var;
	char	*arg_str;

	arg_str = ft_strjoin(env_var_name, arg);
	if (!arg_str)
		return ;
	new_var = ft_lstnew(arg_str);
	if (!new_var)
		return ;
	ft_lstadd_back(head, new_var);
}

void	update_env_var(t_list **head, char *env_var_name ,char *arg)
{
	t_list	*env_var;
	char	*new_arg;

	env_var = ft_lstfind_str(head, env_var_name);
	if (!env_var_name)
	{
		create_env_var(head, env_var_name, arg);
		return ;
	}
	free(env_var->content);
	new_arg = ft_strjoin(env_var_name, arg);
	if (!new_arg)
		return ;
	env_var->content = new_arg;
}

void	remove_env_var(t_list **head, t_list **node)
{
	t_list	*prev;
	t_list	*iter;
	t_list	*next;
	t_list	*node_d;

	if (!head || *head == NULL || !node)
		return ;
	if (ft_lstsize(*head) == 1)
	{
		ft_lstclear(head, free);
		*head = NULL;
		return ;
	}
	iter = *head;
	node_d = *node;
	next = node_d->next;
	while (iter->next != node_d)
	{
		prev = iter;
		iter = iter->next;
	}
	ft_lstdelone(node_d, free);
	prev->next = next;
}