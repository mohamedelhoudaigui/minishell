/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:32:56 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/07 00:32:51 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

char	*return_exit_status(t_info *info)
{
	char	*result;
	char	*tmp;

	result = ft_itoa(g_exit_status);
	tmp = chad_strdup(result, info->alloc_head);
	free(result);
	if (!tmp)
		return (NULL);
	return (tmp);
}
