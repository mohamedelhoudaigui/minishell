/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:04:23 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/18 14:28:01 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_commands	*ft_new_command(char **commands, int in, int out, int out_type)
{
	t_commands	*node;

	node = (t_commands *)malloc(sizeof(t_commands));
	if (!node)
		return (NULL);
	node->command = commands;
	node->in = in;
	node->out = out;
	node->next = NULL;
	node->out_type = out_type;
	return (node);
}

t_commands	*get_last_command(t_commands **head)
{
	t_commands	*iter;

	if (!head || *head == NULL)
		return (NULL);
	iter = *head;
	while (iter->next != NULL)
	{
		iter = iter->next;
	}
	return (iter);
}

void	ft_add_command(t_commands **head, t_commands *node)
{
	t_commands	*last;

	if (!node || !head || *head == NULL)
		return ;	
	last = get_last_command(head);
	last->next = node;
}

void	ft_clear_commands(t_commands **head)
{
	t_commands	*iter;
	t_commands	*tmp;
	int			i;
	char		**args;

	if (!head || *head == NULL)
		return ;
	iter = *head;
	tmp = iter;
	while (iter)
	{
		tmp = iter->next;
		args = iter->command;
		i = 0;
		while (args[i])
			free(args[i++]);
		free(args);
		free(iter);
		iter = tmp;
	}
}