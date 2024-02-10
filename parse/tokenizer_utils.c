/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:11:15 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/09 22:31:10 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

bool	check_line(char *line, t_info *info)
{
	while (line[info->cursor])
	{
		if (!is_space(line[info->cursor]))
			return (TRUE);
		info->cursor += 1;
	}
	return (FALSE);
}

void	default_token(t_oken *head)
{
	if (!head->next || !head->prev)
	{
		head->next = NULL;
		head->prev = NULL;
	}
	head->dollar_presence = FALSE;
	head->quote_type = -1;
	head->data_type = -1;
}

t_oken	*add_token(char *str_token, t_info *info)
{
	size_t	size;
	t_oken	*head;
	t_oken	*token;

	size = sizeof(t_oken);
	head = info->head;
	if (!info->head)
	{
		token = chad_alloc(size, 1, info->alloc_head);
		info->head = token;
		default_token(token);
		token->token = str_token;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		token = chad_alloc(size, 1, info->alloc_head);
		default_token(token);
		head->next = token;
		token->prev = head;
		token->next = NULL;
		token->token = str_token;
	}
	return (token);
}

void	join_quotes(t_oken *head, t_info *info)
{
	t_oken	*token;
	t_oken	*next;

	token = head;
	next = head->next;
	while (next)
	{
		if (token->join_next == TRUE)
		{
			token->token = chad_strjoin(token->token, next->token,
					info->alloc_head);
			token->join_next = next->join_next;
			token->next = next->next;
			next = next->next;
		}
		else
		{
			token = next;
			next = next->next;
		}
	}
}

void	update_quote_type(t_oken *head)
{
	t_oken	*token;

	token = head;
	while (token)
	{
		if (token->token[0] == QUOTE_CHAR)
			token->quote_type = QUOTE;
		else if (token->token[0] == DQUOTE_CHAR)
			token->quote_type = DQUOTE;
		else
			token->quote_type = NO_QUOTE;
		token = token->next;
	}
}
