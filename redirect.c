/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 01:28:24 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/19 02:30:55 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_out(int out)
{
	if (out != 1)
	{
		dup2(1, out);
		close(out);
	}
}

void	redirect_in(int in)
{
	if (in != 0)
	{
		dup2(0, in);
		close(in);
	}
}
