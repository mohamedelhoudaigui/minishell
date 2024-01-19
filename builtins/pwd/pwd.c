/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:53:18 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/19 03:33:36 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd(t_commands *args)
{
	char	buffer[5000];

	redirect_out(args->out);
	redirect_in(args->in);
	if (getcwd(buffer, sizeof(buffer)) != NULL)
		printf("%s\n", buffer);
	else
	{
		perror("pwd");
		return (1);
	}
	return (0);
}