/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:26:41 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/06 17:38:15 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

void	handle_getcwd_cases(char *path, t_list **env_adr)
{
	if (path[0] == '.' && path[1] == '\0')
		join_env_var(env_adr, "PWD=", "/.");
	else if (path[0] == '.' && path[1] == '.' && path[2] == '\0')
		join_env_var(env_adr, "PWD=", "/..");
}

char	*initialize_path(t_list **env_adr, t_commands *command, int *free_after)
{
	char	**args;
	char	*path;

	*free_after = 0;
	args = command->command;
	path = args[1];
	if (path == NULL)
		*free_after = 1;
	path = handle_path_cases(env_adr, &path);
	return (path);
}

int	change_directory(char *path)
{
	if (chdir(path) == -1)
	{
		perror("cd");
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

int	handle_buffer(t_list **env_adr, char *path, char *buffer)
{
	if (getcwd(buffer, 5000) == NULL)
	{
		perror("getcwd");
		change_old_pwd(env_adr);
		handle_getcwd_cases(path, env_adr);
		g_exit_status = 1;
		return (0);
	}
	return (1);
}

int	cd(t_list **env_adr, t_commands *command)
{
	char	*path;
	char	*buffer;
	int		free_after;

	path = initialize_path(env_adr, command, &free_after);
	if (path == NULL)
		return (1);
	if (change_directory(path))
		return (1);
	buffer = (char *)ft_calloc(sizeof(char), 5000);
	if (!buffer)
		return (1);
	if (!handle_buffer(env_adr, path, buffer))
		return (0);
	change_old_pwd(env_adr);
	change_cwd_env(env_adr, buffer);
	free(buffer);
	if (free_after == 1)
		free(path);
	g_exit_status = 0;
	return (0);
}
