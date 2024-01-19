/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_collect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:57:29 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/18 20:58:32 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    clear_garbage(t_garbg *head)
{
    if (!head)
        return ;
    clear_garbage(head->next);
    free(head->ptr);
    free(head);
}

void    *garbage(int size, int len, int status)
{
    static t_garbg    *head;
    void            *ptr;
    t_garbg            *tmp;

    ptr = NULL;
    if (status == 0)
        ptr = ft_calloc(size, len);
    if (!ptr || status == 1)
    {
        clear_garbage(head);
        exit(1);
    }
    tmp = malloc(sizeof(t_garbg));
    if (!tmp)
    {
        free(ptr);
        clear_garbage(head);
        exit(1);
    }
    tmp->ptr = ptr;
    tmp->next = head;
    head = tmp;
    return (ptr);
}