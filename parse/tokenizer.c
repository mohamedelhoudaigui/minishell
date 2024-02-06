/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:10:22 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/06 19:25:48 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"
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

void	handle_operator(char *line, t_info *info)
{
	t_oken	*new_token;

	if (line[info->cursor] == PIPE_CHAR)
	{
		handle_pipe(info);
	}
	else if (line[info->cursor] == REDIR_OUT_CHAR)
	{
		if ((line[info->cursor + 1]) == REDIR_OUT_CHAR)
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
	else if (line[info->cursor] == REDIR_IN_CHAR)
	{
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
}

t_oken	*handle_word(char *line, t_info *info)
{
	char	*str_token;
	t_oken	*new_token;
	int		j;
	int		i;
	int		len;

	j = 0;
	i = info->cursor;
	len = word_len(info);
	str_token = chad_alloc(sizeof(char), len + 1, info->alloc_head);
	while (j < len)
	{
		str_token[j] = line[i];
		j++;
		i++;
	}
	str_token[len] = '\0';
	new_token = add_token(str_token, info);
	if (line[i] == DQUOTE)
		new_token->join_next = TRUE;
	else if (line[i] == QUOTE)
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

	j = 0;
	info->cursor += 1;
	if (!valid_quotes(info))
	{
		parse_error("syntax error : invalid quotes", info);
		return (NULL);
	}
	i = info->cursor;
	len = quote_len(line, info);
	if (len == -1)
		return (NULL);
	str_token = (char *)chad_alloc(1, len + 1, info->alloc_head);
	while (j < len)
	{
		str_token[j] = line[i];
		j++;
		i++;
	}
	str_token[len] = '\0';
	new_token = add_token(str_token, info);
	if (line[info->cursor - 1] == DQUOTE)
		new_token->quote_type = 1;
	else
		new_token->quote_type = 0;
	new_token->data_type = WORD;
	if (line[i + 1] == DQUOTE && line[i + 1] != '\0')
		new_token->join_next = TRUE;
	else if (line[i + 1] == QUOTE && line[i + 1] != '\0' && line[i + 1])
		new_token->join_next = TRUE;
	else if (line[i + 1] != ' ' && line[i + 1] != '\0' && line[i
		+ 1] != PIPE_CHAR && line[i + 1] != REDIR_OUT_CHAR && line[i
		+ 1] != REDIR_IN_CHAR)
		new_token->join_next = TRUE;
	else
		new_token->join_next = FALSE;
	info->cursor += j + 1;
	return (new_token);
}

void	handle_dollar(char *line, t_info *info)
{
	t_oken	*new_token;

	new_token = handle_word(line, info);
	new_token->dollar_presence = TRUE;
}

t_info	*tokenizer(char *line, t_info *info)
{
	if (!check_line(line, info))
		return (NULL);
	while (line[info->cursor])
	{
		if (is_operator(line[info->cursor]))
		{
			handle_operator(line, info);
		}
		else if (line[info->cursor] == DQUOTE || line[info->cursor] == QUOTE)
		{
			if (!handle_quote(line, info))
				return (NULL);
		}
		else if (ft_isprint(line[info->cursor]) && !is_space(line[info->cursor])
			&& !is_operator(line[info->cursor]) && !is_quote(line[info->cursor])
			&& line[info->cursor] != '$')
		{
			handle_word(line, info);
		}
		else if (line[info->cursor] == '$')
			handle_dollar(line, info);
		else if (is_space(line[info->cursor]))
			info->cursor++;
	}
	return (info);
}
