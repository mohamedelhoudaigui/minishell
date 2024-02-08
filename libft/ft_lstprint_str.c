/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:25:35 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/08 15:08:01 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*check_eq(char	*str)
{
	return (ft_strchr(str, '='));
}

void	ft_lstprint_str(t_list *head, int out)
{
	if (!head)
		return ;
	while (head)
	{
		if (check_eq(head->content) != NULL)
			ft_putendl_fd(head->content, out);
		head = head->next;
	}
}
