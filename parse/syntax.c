/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:26:12 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/07 02:53:35 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

bool	is_redir(t_oken *tokens)
{
	if (tokens->data_type == REDIR_IN || tokens->data_type == REDIR_OUT
		|| tokens->data_type == APPEND || tokens->data_type == HEREDOC)
	{
		return (TRUE);
	}
	return (FALSE);
}

bool	check_token_syntax2(t_oken *tokens)
{
	while (tokens->next != NULL)
	{
		if (is_redir(tokens) && is_redir(tokens->next))
			return (g_exit_status = 258,
				printf("syntax error near unexpected token `newline'\n"), TRUE);
		if (tokens->data_type == PIPE && tokens->next->data_type == PIPE)
		{
			return (printf("syntax error near unexpected token `|'\n"),
				g_exit_status = 258, TRUE);
		}
		tokens = tokens->next;
	}
	if (tokens->data_type == PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (g_exit_status = 258, TRUE);
	}
	if (tokens->data_type == REDIR_IN || tokens->data_type == REDIR_OUT
		|| tokens->data_type == HEREDOC || tokens->data_type == APPEND)
		return (printf("syntax error near unexpected token `newline'\n"),
			g_exit_status = 258, TRUE);
	return (FALSE);
}

bool	check_token_syntax(t_oken *tokens)
{
	t_oken	*head;

	head = tokens;
	if (tokens->data_type != WORD && tokens->data_type != PIPE
		&& tokens->next != NULL)
	{
		if (tokens->next->data_type == WORD)
			return (FALSE);
		if (tokens->next->data_type != WORD && tokens->next->data_type != PIPE)
		{
			printf("syntax error near unexpected token `%s'\n",
				tokens->next->token);
			return (g_exit_status = 258, TRUE);
		}
		printf("syntax error near unexpected token `newline'\n");
		return (g_exit_status = 258, TRUE);
	}
	else if (tokens->data_type == PIPE)
		return (printf("syntax error near unexpected token `|'\n"),
			g_exit_status = 258, TRUE);
	if (check_token_syntax2(tokens))
		return (g_exit_status = 258, TRUE);
	tokens = head;
	return (FALSE);
}
