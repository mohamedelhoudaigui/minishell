/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:20:28 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/06 18:56:37 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

int 	pipe_count(t_info *info)
{
	t_oken	*tokens;
	int		count;

	tokens = info->head;
	count = 0;
	while (tokens)
	{
		if (tokens->data_type == 5)
			count++;
		tokens = tokens->next;
	}
	return (count + 1);
}

int	redir_count(t_info *info)
{
	t_oken	*tokens;
	int		count;

	tokens = info->head;
	count = 0;
	while (tokens)
	{
		if (tokens->data_type == 2 || tokens->data_type == 3
			|| tokens->data_type == 4)
			count++;
		tokens = tokens->next;
	}
	return (count);
}