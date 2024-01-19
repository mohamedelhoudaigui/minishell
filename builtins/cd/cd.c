/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:26:41 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/19 03:32:43 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	cd(t_list **env_adr, t_commands *command)
{
	char	*path;
	char	**args;
	char	*buffer;
	
	redirect_out(command->out);
	redirect_in(command->in);
	args = command->command;
	path = args[1];
	if (path[0] == '\0' || (path[0] == '~' && path[1] == '\0'))
		path = change_to_var(env_adr, "HOME=");
	if (path[0] == '-' && path[1] == '\0')
		path = change_to_var(env_adr, "OLDPWD=");
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	buffer = (char *)ft_calloc(sizeof(char), 5000);
	if (!buffer)
		return (1);
	if (getcwd(buffer, 5000) == NULL)
		return (1);
	if (change_old_pwd(env_adr) == 1)
		return (1);
	if (change_cwd_env(env_adr, buffer) == 1)
		return (1);
	free(buffer);
	return (0);
}