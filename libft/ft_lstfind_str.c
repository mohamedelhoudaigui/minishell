/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:05:22 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/08 19:36:29 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	str_find_to(char *s1, char *s2)
{
	int	i;

	if (!s1 && !s2)
		return (0);
	if ((!s1 && s2) || (!s2 && s1))
		return (1);
	i = 0;
	while (s1 && s2 && s1[i] == s2[i])
		i++;
	if (s1[i] == '=' && s2[i] == '\0')
		return (0);
	return (1);
}

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
			if (str_find_to(head->content, compare) == 0)
				return (head);
		}
		head = head->next;
	}
	return (NULL);
}
