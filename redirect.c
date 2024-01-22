/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 01:28:24 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/22 03:29:58 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_out(int out)
{
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
}

void	redirect_in(int in)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
}
