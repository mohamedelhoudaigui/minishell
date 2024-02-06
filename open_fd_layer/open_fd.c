/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 05:00:27 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/05 17:44:57 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"
#include "../inc/parse.h"


t_commands	*open_fd(t_cmd	*commands, t_list **env_adr)
{
	t_commands	*head;
	t_commands	*temp;
	t_redir		*in;
	t_redir		*out;
	char		**args;

	if (!commands)
		return (NULL);
	head = (t_commands *)ft_calloc(1, sizeof(t_commands));
	if (!head)
		return (NULL);
	in = commands->redir;
	out = commands->redir_out;
	args = commands->cmd;
	head->in = handle_in_files(in, env_adr);
	head->out = handle_out_files(out);
	head->command = alloc_commands(args);
	commands = commands->next;
	while (commands)
	{
		temp = (t_commands *)ft_calloc(1, sizeof(t_commands));
		in = commands->redir;
		out = commands->redir_out;
		args = commands->cmd;
		temp->in = handle_in_files(in, env_adr);
		temp->out = handle_out_files(out);
		temp->command = alloc_commands(args);
		command_add_back(&head, temp);
		commands = commands->next;
	}
	return (head);
}
