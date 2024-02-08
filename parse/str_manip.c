/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:22:13 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/08 16:07:37 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

bool	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

bool	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (TRUE);
	return (FALSE);
}

bool	is_quote(char c)
{
	if (c == DQUOTE_CHAR || c == QUOTE_CHAR)
		return (TRUE);
	return (FALSE);
}

void	print_arr(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		printf("%s\n", str[i]);
}

bool	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}
