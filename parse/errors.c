/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:26:25 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/06 23:18:34 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

void	parse_error(const char *exit_msg)
{
	if (exit_msg != NULL)
		printf("%s\n", exit_msg);
	g_exit_status = 258;
}

bool	valid_quotes(t_info *info)
{
	char	*line;
	int		i;

	line = info->line;
	i = info->cursor - 1;
	if (line[i] == DQUOTE)
		return (check_double_quotes(line, &i));
	else if (line[i] == QUOTE)
		return (check_single_quotes(line, &i));
	return (FALSE);
}

bool	check_double_quotes(char *line, int *i)
{
	(*i)++;
	if (line[*i] == DQUOTE)
		return (TRUE);
	while (line[*i])
	{
		if (line[*i] == DQUOTE)
			return (TRUE);
		(*i)++;
	}
	return (FALSE);
}

bool	check_single_quotes(char *line, int *i)
{
	(*i)++;
	if (line[*i] == QUOTE)
		return (TRUE);
	while (line[*i])
	{
		if (line[*i] == QUOTE)
			return (TRUE);
		(*i)++;
	}
	return (FALSE);
}
