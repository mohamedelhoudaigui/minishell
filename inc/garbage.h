/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:57:42 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/07 02:57:44 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

# include <stdlib.h>

typedef struct s_alloc
{
	void			*address;
	void			*alloc_node;
	struct s_alloc	*next;
}					t_alloc;

void				add_address(void *address, t_alloc *head);
void				*chad_alloc(size_t size, int quantity, t_alloc *head);
void				free_all(t_alloc *head);

#endif
