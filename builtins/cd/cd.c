/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:26:41 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/04 14:22:46 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	change_old_pwd(t_list **env_var)
{
	t_list	*pwd;

	pwd = ft_lstfind_str(env_var, "PWD=");
	if (!pwd)
		return (1);
	update_env_var(env_var, "OLDPWD=", &pwd->content[4]);
	return (0);
}

char	*change_to_var(t_list **env_adr, char *var_name)
{
	t_list	*var;
	char	*new_path;

	var = ft_lstfind_str(env_adr, var_name);
	if (!var)
		return (NULL);
	new_path = ft_strdup(&var->content[ft_strlen(var_name)]);
	if (!new_path)
		return (NULL);
	return (new_path);
}


int	change_cwd_env(t_list **env_var, char *path)
{
	update_env_var(env_var, "PWD=", path);
	return (0);
}

char	*handle_path_cases(t_list **env_adr, char **path_d)
{
	char	*path;

	path = *path_d;
	if (path == NULL)
		path = change_to_var(env_adr, "HOME=");
	if (path == NULL)
	{
		ft_putstr_fd("cd : HOME not set\n", 2);
		exit_status = 1;
	}
	return (path);
}

void	handle_getcwd_cases(char *path, t_list **env_adr)
{
	if (path[0] == '.' && path[1] == '\0')
		join_env_var(env_adr, "PWD=", "/.");
	else if (path[0] == '.' && path[1] == '.' && path[2] == '\0')
		join_env_var(env_adr, "PWD=", "/..");
}

int	cd(t_list **env_adr, t_commands *command)
{
	char	*path;
	char	**args;
	char	*buffer;
	int		free_after;
	
	free_after = 0;
	args = command->command;
	path = args[1];
	if (path == NULL)
		free_after = 1;
	path = handle_path_cases(env_adr, &path);
	if (path == NULL)
		return (1);
	if (chdir(path) == -1)
	{
		perror("cd");
		exit_status = 1;
		return (1);
	}
	buffer = (char *)ft_calloc(sizeof(char), 5000);
	if (!buffer)
		return (1);
	if (getcwd(buffer, 5000) == NULL)
	{
		perror("getcwd");
		change_old_pwd(env_adr);
		handle_getcwd_cases(path, env_adr);
		exit_status = 1;
		return (0);
	}
	change_old_pwd(env_adr);
	change_cwd_env(env_adr, buffer);
	free(buffer);
	if (free_after == 1)
		free(path);
	exit_status = 0;
	return (0);
}