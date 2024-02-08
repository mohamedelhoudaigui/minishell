/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:32:56 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/08 18:29:29 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

char	*return_exit_status(t_info *info)
{
	char	*result;
	char	*str;

	str = ft_itoa(g_exit_status);
	if (!str)
		return (NULL);
	result = chad_strdup(str, info->alloc_head);
	free(str);
	if (!result)
		return (NULL);
	return (result);
}
