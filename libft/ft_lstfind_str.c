/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:05:22 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/06 22:58:20 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
