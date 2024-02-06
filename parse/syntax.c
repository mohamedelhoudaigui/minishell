/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:26:12 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/06 18:32:40 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

bool	check_token_syntax(t_oken *tokens)
{
	t_oken	*head;

	//	free on exit
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
			return (TRUE);
		}
		printf("syntax error near unexpected token `newline'\n");
		return (TRUE);
	}
	else if (tokens->data_type == PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (TRUE);
	}
	while (tokens->next != NULL)
	{
		tokens = tokens->next;
	}
	if (tokens->data_type == PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (TRUE);
	}
	if (tokens->data_type == REDIR_IN || tokens->data_type == REDIR_OUT
		|| tokens->data_type == HEREDOC || tokens->data_type == APPEND)
	{
		printf("syntax error near unexpected token `newline'\n");
		return (TRUE);
	}
	tokens = head; // reset
	return (FALSE);
}