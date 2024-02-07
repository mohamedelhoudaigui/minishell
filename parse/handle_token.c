/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 23:12:50 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/06 23:27:21 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

void	handle_pipe(t_info *info)
{
	t_oken	*new_token;
	char	*str_token;

	str_token = chad_alloc(1, 2, info->alloc_head);
	str_token[0] = PIPE_CHAR;
	str_token[1] = '\0';
	new_token = add_token(str_token, info);
	new_token->data_type = PIPE;
	info->cursor += 1;
}

void	handle_redirection_out(char *line, t_info *info)
{
	t_oken	*new_token;

	if (line[info->cursor + 1] == REDIR_OUT_CHAR)
	{
		new_token = add_token(chad_strdup(">>", info->alloc_head), info);
		new_token->data_type = 4;
		info->cursor += 2;
	}
	else
	{
		new_token = add_token(chad_strdup(">", info->alloc_head), info);
		new_token->data_type = 2;
		info->cursor += 1;
	}
}

void	handle_redirection_in(char *line, t_info *info)
{
	t_oken	*new_token;

	if (line[info->cursor + 1] == REDIR_IN_CHAR)
	{
		new_token = add_token(chad_strdup("<<", info->alloc_head), info);
		new_token->data_type = 3;
		info->cursor += 2;
	}
	else
	{
		chad_strdup("<", info->alloc_head);
		new_token = add_token(chad_strdup("<", info->alloc_head), info);
		new_token->data_type = 1;
		info->cursor += 1;
	}
}

t_oken	*handle_word(char *line, t_info *info)
{
	char	*str_token;
	t_oken	*new_token;
	int		j;
	int		i;
	int		len;

	j = -1;
	i = info->cursor;
	len = word_len(info);
	str_token = chad_alloc(sizeof(char), len + 1, info->alloc_head);
	while (++j < len)
	{
		str_token[j] = line[i];
		i++;
	}
	str_token[len] = '\0';
	new_token = add_token(str_token, info);
	if (line[i] == DQUOTE || line[i] == QUOTE)
		new_token->join_next = TRUE;
	else
		new_token->join_next = FALSE;
	info->cursor = i;
	new_token->data_type = 6;
	return (new_token);
}

t_oken	*handle_quote(char *line, t_info *info)
{
	char	*str_token;
	t_oken	*new_token;
	int		j;
	int		i;
	int		len;

	j = -1;
	info->cursor += 1;
	if (!valid_quotes(info))
	{
		parse_error("syntax error : invalid quotes");
		return (NULL);
	}
	i = info->cursor - 1;
	len = quote_len(line, info);
	if (len == -1)
		return (NULL);
	str_token = (char *)chad_alloc(1, len + 1, info->alloc_head);
	while (++j < len)
		str_token[j] = line[++i];
	str_token[len] = '\0';
	new_token = add_token(str_token, info);
	info = extract_token_stats(new_token, info, i, j);
	return (new_token);
}
