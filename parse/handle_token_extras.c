/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token_extras.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 23:23:45 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/09 17:13:50 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

void	handle_dollar(char *line, t_info *info)
{
	t_oken	*new_token;

	new_token = handle_word(line, info);
	new_token->dollar_presence = TRUE;
}

t_info	*extract_token_stats(t_oken *new_token, t_info *info, int i, int j)
{
	char	*line;

	line = info->line;
	if (line[info->cursor - 1] == DQUOTE_CHAR)
		new_token->quote_type = 1;
	else
		new_token->quote_type = 0;
	new_token->data_type = WORD;
	i++;
	if (line[i + 1] == DQUOTE_CHAR && line[i + 1] != '\0')
		new_token->join_next = TRUE;
	else if (line[i + 1] == QUOTE_CHAR && line[i + 1] != '\0' && line[i + 1])
		new_token->join_next = TRUE;
	else if (line[i + 1] != ' ' && line[i + 1] != '\0'
		&& line[i + 1] != PIPE_CHAR && line[i + 1] != REDIR_OUT_CHAR
		&& line[i + 1] != REDIR_IN_CHAR)
		new_token->join_next = TRUE;
	else
		new_token->join_next = FALSE;
	info->cursor += j + 1;
	return (info);
}

void	handle_operator(char *line, t_info *info)
{
	if (line[info->cursor] == PIPE_CHAR)
		handle_pipe(info);
	else if (line[info->cursor] == REDIR_OUT_CHAR)
		handle_redirection_out(line, info);
	else if (line[info->cursor] == REDIR_IN_CHAR)
		handle_redirection_in(line, info);
}
