/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:49:24 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/06 22:05:44 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

void	handle_redir_out(t_oken *tokens, t_info *info, t_cmd *cmd)
{
	t_redir	*redir;
	t_redir	*head;
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

void	handle_redir_in(t_oken *tokens, t_info *info, t_cmd *cmd)
{
	t_redir	*redir;
	t_redir	*head;
	char	*file;
	int		type;

	type = -1;
	if (tokens->data_type == REDIR_IN)
		type = REDIR_IN;
	else if (tokens->data_type == HEREDOC)
		type = HEREDOC;
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
	redir->type = type;
	redir->file = file;
	redir->next = NULL;
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

void	handle_word_and_expand(t_oken *tokens, t_info *info, t_cmd *cmd, int i)
{
	t_list **env;
	char *tmp;
	char *expanded;
	char *result;
	unsigned long j;
	int k;

	j = 1;
	k = 0;
	env = info->env;
	if (tokens->data_type == WORD && loop_dollar_presence(tokens) == FALSE)
		cmd->cmd[i] = tokens->token;
	else if (loop_dollar_presence(tokens) == TRUE && tokens->quote_type == 1
		&& tokens->token[0] == '\'')
	{
		tmp = chad_alloc(sizeof(char), ft_strlen(tokens->token) - 1,
				info->alloc_head);
		while (j < ft_strlen(tokens->token) - 1)
		{
			tmp[k] = tokens->token[j];
			j++;
			k++;
		}
		tmp[k] = '\0';
		expanded = chad_expand(env, tmp, info);
		result = chad_alloc(sizeof(char), ft_strlen(expanded) + 1,
				info->alloc_head);
		result[0] = '\'';
		j = 1;
		k = 0;
		while (j < ft_strlen(tokens->token) + 3)
		{
			result[j] = expanded[k];
			j++;
			k++;
		}
		result[ft_strlen(expanded) + 1] = '\'';
		result[ft_strlen(expanded) + 2] = '\0';
		cmd->cmd[i] = result;
	}
	else if (tokens->data_type == WORD && tokens->dollar_presence == TRUE
		&& tokens->quote_type != 1 && tokens->quote_type != 0)
	{
		cmd->cmd[i] = chad_expand(env, tokens->token, info);
    }
	else if (tokens->quote_type == 0)
		cmd->cmd[i] = tokens->token;
	else if (tokens->quote_type == 1) 
		cmd->cmd[i] = chad_expand(env, tokens->token, info);

}