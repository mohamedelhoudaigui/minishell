/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_extras.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:06:59 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/07 03:53:04 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

void	handle_redir_in2(t_cmd *cmd, t_redir *redir)
{
	t_redir	*head;

	if (cmd->redir == NULL)
		cmd->redir = redir;
	else
	{
		head = cmd->redir;
		while (head->next != NULL)
			head = head->next;
		head->next = redir;
	}
}

int	redir_type(t_oken *tokens)
{
	if (tokens->data_type == REDIR_IN)
		return (REDIR_IN);
	else if (tokens->data_type == HEREDOC)
		return (HEREDOC);
	return (-1);
}

void	handle_redir_out2(t_cmd *cmd, t_redir *redir)
{
	t_redir	*head;

	if (cmd->redir_out == NULL)
		cmd->redir_out = redir;
	else
	{
		head = cmd->redir_out;
		while (head->next != NULL)
			head = head->next;
		head->next = redir;
	}
}

void	handle_redir_out(t_oken *tokens, t_info *info, t_cmd *cmd)
{
	t_redir	*redir;
	char	*file;
	int		type;

	type = -1;
	if (tokens->data_type == REDIR_OUT)
		type = REDIR_OUT;
	else if (tokens->data_type == APPEND)
		type = APPEND;
	file = tokens->next->token;
	if (file[0] == '$')
		file = chad_expand(info->env, file, info);
	redir = chad_alloc(sizeof(t_redir), 1, info->alloc_head);
	redir->type = type;
	redir->file = file;
	redir->next = NULL;
	handle_redir_out2(cmd, redir);
}

void	handle_redir_in(t_oken *tokens, t_info *info, t_cmd *cmd)
{
	t_redir	*redir;
	char	*file;
	int		type;

	type = -1;
	file = tokens->next->token;
	if (file[0] == '$')
		file = chad_expand(info->env, file, info);
	redir = chad_alloc(sizeof(t_redir), 1, info->alloc_head);
	if (tokens->data_type == HEREDOC)
	{
		if (tokens->next->quote_type == 1 || tokens->next->quote_type == 0)
			redir->heredoc_ex = FALSE;
		else
			redir->heredoc_ex = TRUE;
	}
	redir->type = redir_type(tokens);
	redir->file = file;
	redir->next = NULL;
	handle_redir_in2(cmd, redir);
}
