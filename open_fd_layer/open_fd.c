/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 05:00:27 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/08 15:46:12 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"
#include "../inc/parse.h"

t_commands	*create_command_node(t_cmd *commands, t_list **env_adr)
{
	t_commands	*temp;
	t_redir		*in;
	t_redir		*out;
	char		**args;

	temp = (t_commands *)ft_calloc(1, sizeof(t_commands));
	in = commands->redir;
	out = commands->redir_out;
	args = commands->cmd;
	temp->in = handle_in_files(in, env_adr);
	temp->out = handle_out_files(out);
	temp->command = alloc_commands(args);
	return (temp);
}

t_commands	*open_fd(t_cmd *commands, t_list **env_adr)
{
	t_commands	*head;
	t_commands	*temp;

	if (!commands)
		return (NULL);
	head = create_command_node(commands, env_adr);
	commands = commands->next;
	while (commands)
	{
		temp = create_command_node(commands, env_adr);
		command_add_back(&head, temp);
		commands = commands->next;
	}
	return (head);
}
