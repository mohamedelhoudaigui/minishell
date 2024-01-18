/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:55:27 by mel-houd          #+#    #+#             */
/*   Updated: 2023/11/09 11:35:24 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;
	t_list	*root;

	if (!*lst || !del)
		return ;
	root = *lst;
	while (root)
	{
		next = root->next;
		ft_lstdelone(root, del);
		root = next;
	}
	*lst = 0;
}
