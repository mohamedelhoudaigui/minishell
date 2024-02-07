/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:20:05 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/06 20:37:08 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

int	quote_len(char *line, t_info *info)
{
	int	i;
	int	j;

	i = info->cursor;
	j = 0;
	if (line[i] && line[i - 1] == 34)
		return (get_quote_length(line, i, j, 34));
	else if (line[i - 1] == 39)
		return (get_quote_length(line, i, j, 39));
	return (-1);
}

int	get_quote_length(char *line, int i, int j, char quote_type)
{
	while (line[i])
	{
		if (line[i] && line[i] == quote_type)
			return (j);
		i++;
		j++;
	}
	return (-1);
}

int	last_char_in_word(char *line, t_info *info)
{
	int	i;

	i = info->cursor;
	while (line[i] != '\0' && !is_space(line[i]) && !is_quote(line[i]))
		i++;
	i--;
	return (i);
}

int	word_len(t_info *info)
{
	int	i;
	int	j;

	i = info->cursor;
	j = 0;
	while (info->line[i] != '\0' && !is_space(info->line[i])
		&& !is_quote(info->line[i]) && !is_operator(info->line[i]))
	{
		i++;
		j++;
	}
	return (j);
}
