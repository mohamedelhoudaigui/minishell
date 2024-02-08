/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:53:18 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/08 18:13:32 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	pwd(t_commands *args, t_list **env_adr)
{
	char	buffer[5000];
	t_list	*node;

	(void)args;
	if (getcwd(buffer, sizeof(buffer)) != NULL)
	{
		g_exit_status = 0;
		printf("%s\n", buffer);
	}
	else
	{
		node = ft_lstfind_str(env_adr, "PWD=");
		if (node == NULL)
		{
			g_exit_status = 1;
			perror("pwd");
		}
		else
		{
			printf("%s\n", node->content + 4);
			g_exit_status = 0;
		}
	}
	return (g_exit_status);
}
