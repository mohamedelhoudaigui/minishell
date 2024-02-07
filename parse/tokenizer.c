/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:10:22 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/06 22:11:40 by mlamkadm         ###   ########.fr       */
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
