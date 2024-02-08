/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:10:22 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/08 16:07:37 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"
#include "../inc/parse.h"

t_info	*tokenizer(char *line, t_info *info)
{
	if (!check_line(line, info))
		return (NULL);
	while (line[info->cursor])
	{
		if (is_operator(line[info->cursor]))
			handle_operator(line, info);
		else if (line[info->cursor] == DQUOTE_CHAR || line[info->cursor] == QUOTE_CHAR)
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
