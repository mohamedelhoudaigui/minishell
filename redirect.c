/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 01:28:24 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/28 03:37:05 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_out(int out)
{
	if (out != 1)
	{
		if (dup2(out, 1) == -1)
		{
			perror("dup2");
			return ;
		}
		close(out);
	}
}

void	redirect_in(int in)
{
	if (in != 0)
	{
		if (dup2(in, 0) == -1)
		{
			perror("dup2");
			return ;
		}
		close(in);
	}
}
