/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:21:56 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/06 17:26:25 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execution.h"

void	add_env_var(t_list **env_var, char *var_value)
{
	char	*var;
	t_list	*node;

	var = ft_strdup(var_value);
	if (!var)
		return ;
	node = ft_lstnew(var);
	if (!node)
		return ;
	ft_lstadd_back(env_var, node);
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

void	handle_head_node(t_list **head, t_list **node)
{
	t_list	*node_d;

	if (ft_lstsize(*head) == 1)
	{
		*head = (*node)->next;
		(*node)->next = NULL;
		ft_lstdelone(*node, free);
		return ;
	}
	else if ((*head)->next != NULL)
	{
		node_d = (*head)->next;
		*head = node_d;
		ft_lstdelone(*node, free);
		return ;
	}
	ft_lstclear(head, free);
	*head = NULL;
}

void	handle_other_nodes(t_list **head, t_list **node)
{
	t_list	*prev;
	t_list	*iter;
	t_list	*next;
	t_list	*node_d;

	node_d = *node;
	next = node_d->next;
	iter = *head;
	while (iter)
	{
		prev = iter;
		iter = iter->next;
		if (iter == node_d)
			break ;
	}
	iter->next = NULL;
	prev->next = next;
	ft_lstdelone(*node, free);
}

void	remove_env_var(t_list **head, t_list **node)
{
	if (!head || *head == NULL || !node)
		return ;
	if (*node == *head)
	{
		handle_head_node(head, node);
	}
	else
	{
		handle_other_nodes(head, node);
	}
}
