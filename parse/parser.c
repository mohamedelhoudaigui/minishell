/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 23:54:43 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/09 22:39:16 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

t_cmd	*parser_handle_pipe(t_oken *tokens, t_info *info, t_cmd *cmd, int i)
{
	int	word_count;

	cmd->cmd[i] = NULL;
	cmd->next = chad_alloc(sizeof(t_cmd), 1, info->alloc_head);
	cmd = cmd->next;
	cmd->redir = NULL;
	cmd->redir_out = NULL;
	word_count = words_before_pipe(tokens->next) + 1;
	cmd->cmd = chad_alloc(sizeof(char *), word_count, info->alloc_head);
	tokens = tokens->next;
	return (cmd);
}

void	parser_while(t_oken *tokens, t_info *info, t_cmd *cmd, int i)
{
	while (tokens != NULL)
	{
		if (tokens->data_type == PIPE)
		{
			cmd = parser_handle_pipe(tokens, info, cmd, i);
			tokens = tokens->next;
			i = 0;
			continue ;
		}
		if (parser_handle_redir(cmd, info, tokens))
		{
			tokens = tokens->next->next;
			continue ;
		}
		if (tokens->data_type == WORD)
			cmd->cmd[i] = tokens->token;
		if (tokens->next == NULL)
		{
			cmd->cmd[i + 1] = NULL;
			break ;
		}
		tokens = tokens->next;
		i++;
	}
}

bool	parser_handle_redir(t_cmd *cmd, t_info *info, t_oken *tokens)
{
	if (tokens->data_type == REDIR_OUT || tokens->data_type == APPEND)
		return (handle_redir_out(tokens, info, cmd), TRUE);
	if (tokens->data_type == REDIR_IN || tokens->data_type == HEREDOC)
		return (handle_redir_in(tokens, info, cmd), TRUE);
	return (FALSE);
}

t_cmd	*parser(t_info *info)
{
	int		word_count;
	t_cmd	*cmd;
	t_oken	*tokens;
	t_list	**env;
	int		i;

	tokens = info->head;
	env = info->env;
	if (check_token_syntax(tokens))
		return (NULL);
	word_count = words_before_pipe(tokens) + 1;
	cmd = chad_alloc(sizeof(t_cmd), 1, info->alloc_head);
	info->tmp = cmd;
	cmd->cmd = chad_alloc(sizeof(char *), word_count, info->alloc_head);
	info->cmd = cmd;
	i = 0;
	parser_while(tokens, info, cmd, i);
	return (info->cmd);
}
