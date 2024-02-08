/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:32:56 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/06 20:43:09 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

char	*return_exit_status(void)
{
	char	*result;

	result = ft_itoa(g_exit_status);
	if (!result)
		return (NULL);
	return (result);
}
