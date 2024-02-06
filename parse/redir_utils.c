/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:50:17 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/06 19:00:51 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

bool	loop_dollar_presence(t_oken *tokens)
{
	int	i;

	i = 0;
	while (tokens->token[i])
	{
		if (tokens->token[i] == '$')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	words_before_pipe(t_oken *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->data_type == 5 || tokens == NULL)
			return (count);
		else
			count++;
		tokens = tokens->next;
	}
	return (count);
}

int	return_dollar_index(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}