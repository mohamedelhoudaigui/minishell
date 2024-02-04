/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:19:33 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/04 14:22:27 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"

char	**morph_env(t_list *env_var)
{
	char	**env;
	int		size;
	int		i;

	if (!env_var || env_var->content == NULL)
		return (NULL);
	size = ft_lstsize(env_var);
	env = (char **)ft_calloc(sizeof(char *), size + 1);
	if (!env)
		return (NULL);
	i = 0;
	while (i < size)
	{
		env[i] = ft_strdup(env_var->content);
		i++;
		env_var = env_var->next;
	}
	return (env);
}

char	**morph_args(t_commands *args)
{
	char	**old_args;
	int		i;
	char	**args_str;
	int		size;

	if(!args || args->command == NULL)
		return (NULL);
	old_args = args->command;
	size = ft_ptrsize((void **)old_args);
	if (size == -1)
		return (NULL);
	args_str = (char **)ft_calloc(sizeof(char *), size + 1);
	if (!args_str)
		return (NULL);
	i = 0;
	while (old_args[i])
	{
		args_str[i] = ft_strdup(old_args[i]);
		i++;
	}
	return (args_str);
}

char	*check_command_help(char *com, char **path_splited, int key)
{
	int		i;
	char	*str;

	i = 0;
	while (path_splited[i])
	{
		str = ft_strjoin(path_splited[i], com);
		if (access(str, X_OK) == 0 || errno != 2)
		{
			free(com);
			com = str;
			key = 1;
			break ;
		}
		i++;
		free(str);
	}
	if (key == 1)
		return (com);
	return (NULL);
}

char	*check_command(char *command, char **path_splited)
{
	int		key;
	char	*new_com;

	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, X_OK) == 0)
			return (command);
		else
			return (NULL);
	}
	key = 0;
	if (path_splited == NULL)
		return (NULL);
	new_com = ft_strjoin("/", command);
	free(command);
	command = new_com;
	return (check_command_help(command, path_splited, key));
}

char	**split_path(char **env)
{
	int		i;
	char	*path;
	char	**splited_path;

	i = 0;
	if (env == NULL || env[i] == NULL)
		return (NULL);
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 6))
			break ;
		i++;
	}
	path = ft_strtrim(env[i], "PATH=");
	if (!path)
		return (NULL);
	splited_path = ft_split(path, ":");
	if (!splited_path)
	{
		free(path);
		return (NULL);
	}
	free(path);
	return (splited_path);
}

int	execute_command(t_list *env_var, t_commands *args)
{
	int		exit_status;
	char	**env;
	char	**args_str;
	char	*checked_args;
	char	**splited_path;

	exit_status = 0;
	env = morph_env(env_var);
	args_str = morph_args(args);
	splited_path = split_path(env);
	checked_args = check_command(args_str[0], splited_path);
	execve(args_str[0], args_str, env);
	perror("bash");
	if (errno == 13)
		exit(126);
	exit(127);
}