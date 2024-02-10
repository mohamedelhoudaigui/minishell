/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:05:22 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/09 23:18:27 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_list	*ft_lstfind_str(t_list **list, char *compare)
{
	t_list	*head;

	if (!list)
		return (NULL);
	head = *list;
	if (!head)
		return (NULL);
	while (head)
	{
		if (head->content != NULL)
		{
			if (ft_strncmp(head->content, compare, ft_strlen(compare)) == 0)
				return (head);
		}
		head = head->next;
	}
	return (NULL);
}
