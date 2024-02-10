/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:25:35 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/10 00:12:43 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_eq(char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	if (str[++i] == '\0')
		return (1);
	return (0);
}

void	ft_lstprint_str(t_list *head, int out)
{
	if (!head)
		return ;
	while (head)
	{
		if (check_eq(head->content) == 0)
			ft_putendl_fd(head->content, out);
		head = head->next;
	}
}
