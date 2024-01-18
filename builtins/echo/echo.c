/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 01:09:21 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/18 14:35:59 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_flag(char *flag)
{
	int	i;

	i = 1;
	if (!flag || flag[0] == '\0' || flag[0] != '-')
		return (0);
	if (flag[i] == '\0')
		return (false);
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	call_expander(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		printf("%c", str[i]);
		i++;
	}
	return ;
}

int	echo(t_commands *command)
{
	int		i;
	bool	flag;
	char	*str;
	char	**args;

	if (command->out != 1)
	{
		dup2(1, command->out);
		close(command->out);
	}
	args = command->command;
	flag = check_flag(args[1]);
	i = 1;
	while (check_flag(args[i]) == 1)
		i++;
	if (args[i] != NULL)
	{
		while (args[i])
		{
			str = args[i];
			call_expander(str);
			if (args[i + 1])
				printf(" ");
			i++;
		}
	}
	if (flag == 0)
		printf("\n");
	return (0);
}
